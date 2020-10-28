// dear imgui: standalone example application for SDL2 + OpenGL
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h>            // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

void CosmeticEditProcess();

// Main code
int main(int, char**)
{
	// Setup SDL
	// (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
	// depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	// Decide GL+GLSL versions
#ifdef __APPLE__
	// GL 3.2 Core + GLSL 150
	const char* glsl_version = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

	// Create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window* window = SDL_CreateWindow("Driver 2 Cosmetic Editor 1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
	bool err = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
	bool err = false;
	glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
	bool err = false;
	glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name); });
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	// Our state
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	bool done = false;
	while (!done)
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		// FIXME: other apps?
		CosmeticEditProcess();

		// Rendering
		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

// include some PSX stuff
typedef long long OTTYPE;

#include "LIBSPU.H"
#include "LIBGTE.H"
#include "LIBGPU.H"

#include "DR2TYPES.H"

#define MAX_COSMETICS 13

CAR_COSMETICS gCosmetics[MAX_COSMETICS];
int cosmeticOffsets[MAX_COSMETICS];
int gNumCosmeticsLoaded = 0;

void ReadCosmeticsFile(const char* name)
{
	char filename[512];
	sprintf(filename, "DRIVER2/LEVELS/%s.LCF", name);
	
	gNumCosmeticsLoaded = 0;

	FILE* fp = fopen(filename, "rb");
	if(fp)
	{
		fread(cosmeticOffsets, sizeof(cosmeticOffsets), 1, fp);

		for(int i = 0; i < MAX_COSMETICS; i++)
		{
			size_t curPos = ftell(fp);
			
			fseek(fp, cosmeticOffsets[i], SEEK_SET);
			
			fread(&gCosmetics[i], sizeof(CAR_COSMETICS), 1, fp);
			gNumCosmeticsLoaded++;

			fseek(fp, curPos, SEEK_SET);
		}
		
		fclose(fp);
	}
}

void CosmeticEditProcess()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::BeginMenu("Open"))
			{
				if (ImGui::MenuItem("CHICAGO"))
				{
					ReadCosmeticsFile("CHICAGO");
				}

				if (ImGui::MenuItem("HAVANA"))
				{
					ReadCosmeticsFile("HAVANA");
				}

				if (ImGui::MenuItem("VEGAS"))
				{
					ReadCosmeticsFile("VEGAS");
				}

				if (ImGui::MenuItem("RIO"))
				{
					ReadCosmeticsFile("RIO");
				}
				
				ImGui::EndMenu();
			}
			
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{

			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	bool show_demo_window = true;
	bool show_another_window = false;
	
	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	static float f = 0.0f;
	static int counter = 0;


	if(gNumCosmeticsLoaded)
	{
		if(ImGui::Begin("Cosmetic editor", 0, ImGuiWindowFlags_AlwaysAutoResize))                          // Create a window called "Hello, world!" and append into it.
		{
			char text[32];
			static int currentCosmetic = 0;

			sprintf(text, "%d\n", currentCosmetic);
			if (ImGui::BeginCombo("Car", text, 0))
			{
				for (int i = 0; i < gNumCosmeticsLoaded; i++)
				{
					sprintf(text, "Car %d\n", i);
					const bool is_selected = (currentCosmetic == i);
					
					if (ImGui::Selectable(text, is_selected))
						currentCosmetic = i;

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			CAR_COSMETICS* car_cos = &gCosmetics[currentCosmetic];
			int dragval;
			uint flagval;

			dragval = car_cos->powerRatio;
			ImGui::DragInt("Power ratio", &dragval);
			car_cos->powerRatio = dragval;

			dragval = car_cos->susCoeff;
			ImGui::DragInt("Suspension coeff", &dragval);
			car_cos->susCoeff = dragval;
	
			dragval = car_cos->traction;
			ImGui::DragInt("Traction", &dragval);
			car_cos->traction = dragval;

			dragval = car_cos->wheelSize;
			ImGui::DragInt("Wheel size", &dragval);
			car_cos->wheelSize = dragval;

			dragval = car_cos->mass;
			ImGui::DragInt("mass", &dragval);
			car_cos->mass = dragval;

			// twist
			ImGui::NewLine();

			ImGui::BeginGroup();
			{
				
				dragval = car_cos->twistRateX;
				ImGui::DragInt("Angular twist X", &dragval);
				car_cos->twistRateX = dragval;
				ImGui::SameLine();

				dragval = car_cos->twistRateY;
				ImGui::DragInt("Angular twist Y", &dragval);
				car_cos->twistRateY = dragval;
				ImGui::SameLine();

				dragval = car_cos->twistRateZ;
				ImGui::DragInt("Angular twist Z", &dragval);
				car_cos->twistRateZ = dragval;
			}
			ImGui::EndGroup();
	
			ImGui::NewLine();

			ImGui::Text("Brake lights");
			ImGui::BeginGroup();
			{
				flagval = car_cos->extraInfo;
				ImGui::CheckboxFlags("Enabled", &flagval, 8);

				if(flagval & 8)
				{
					ImGui::CheckboxFlags("Double brake lights", &flagval, 0x4000);

					if(flagval & 0x4000)
					{						
						ImGui::CheckboxFlags("Vertical brake lights", &flagval, 0x1000);

						int offset = (flagval & 0x300) >> 6;
						flagval &= ~(12 << 6);
						ImGui::SliderInt("Offset", &offset, 0, 12);
						flagval |= offset << 6 & 0x300;
					}
				}

				car_cos->extraInfo = flagval;
			
			}
			ImGui::EndGroup();

			ImGui::NewLine();

			ImGui::Text("Head lights");
			ImGui::BeginGroup();
			{
				flagval = car_cos->extraInfo;

				ImGui::CheckboxFlags("Double headlight", &flagval, 0x8000);

				if(flagval & 0x8000)
				{
					ImGui::CheckboxFlags("Vertical headlight", &flagval, 0x2000);

					int offset = ((flagval & 0xC00) >> 8);
					flagval &= ~(12 << 8);
					ImGui::SliderInt("Offset", &offset, 0, 12);
					flagval |= offset << 8 & 0xC00;
				}

				car_cos->extraInfo = flagval;

			}
			ImGui::EndGroup();

			/*
			struct SVECTOR headLight; // size=8, offset=0
			struct SVECTOR frontInd; // size=8, offset=8
			struct SVECTOR backInd; // size=8, offset=16
			struct SVECTOR brakeLight; // size=8, offset=24
			struct SVECTOR revLight; // size=8, offset=32
			struct SVECTOR policeLight; // size=8, offset=40
			struct SVECTOR exhaust; // size=8, offset=48
			struct SVECTOR smoke; // size=8, offset=56
			struct SVECTOR fire; // size=8, offset=64
			struct SVECTOR wheelDisp[4]; // size=32, offset=72
			
			short extraInfo; // size=0, offset=104
			
			struct SVECTOR cPoints[12]; // size=96, offset=116
			struct SVECTOR colBox; // size=8, offset=212
			struct SVECTOR cog; // size=8, offset=220
			/*
			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;

			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			*/
			ImGui::End();
		}
	}


	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");

		if (ImGui::Button("Close Me"))
			show_another_window = false;
		
		ImGui::End();
	}
}