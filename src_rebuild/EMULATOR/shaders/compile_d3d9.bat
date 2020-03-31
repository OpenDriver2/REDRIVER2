fxc /nologo /T vs_3_0 /O3 /Gec /Vn gte_shader_vs /Fh gte_shader_vs.h gte_shader.hlsl /DVERTEX
fxc /nologo /T ps_3_0 /O3 /Gec /Vn gte_shader_ps /Fh gte_shader_ps.h gte_shader.hlsl /DPIXEL
fxc /nologo /T vs_3_0 /O3 /Gec /Vn blit_shader_vs /Fh blit_shader_vs.h blit_shader.hlsl /DVERTEX
fxc /nologo /T ps_3_0 /O3 /Gec /Vn blit_shader_ps /Fh blit_shader_ps.h blit_shader.hlsl /DPIXEL
