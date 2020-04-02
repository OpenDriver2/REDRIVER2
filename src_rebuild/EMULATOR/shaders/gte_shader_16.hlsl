struct VS_INPUT {
	float4 a_position : POSITION;
	float4 a_texcoord : TEXCOORD0;
	float4 a_color    : COLOR0;
};

struct VS_OUTPUT {
	float4 v_position  : POSITION;
	float4 v_texcoord  : TEXCOORD0;
	float4 v_color     : TEXCOORD1;
};

#ifdef VERTEX
	float4x4 Projection : register(c0);

	VS_OUTPUT main(VS_INPUT In) {
		VS_OUTPUT Out;
		float2 page;
		page.x = frac (In.a_position.z / 16.0) * 1024.0;
		page.y = floor(In.a_position.z / 16.0) * 256.0;
		Out.v_texcoord     = In.a_texcoord;
		Out.v_texcoord.xy += page;
		Out.v_texcoord.xy *= float2(1.0 / 1024.0, 1.0 / 512.0);
		Out.v_color        = In.a_color;
		Out.v_color.xyz   *= In.a_texcoord.z;
		Out.v_position     = mul(Projection, float4(In.a_position.xy, 0.0, 1.0));
		return Out;
	}
#else
	sampler2D s_texture : register(s0);

	float4 main(VS_OUTPUT In, float2 coord : VPOS) : COLOR0 {
		float2 color_rg = tex2D(s_texture, In.v_texcoord.xy).ra * 255.0;
		float color_16 = color_rg.y * 256.0 + color_rg.x;
		clip(color_16 - 0.001);

		float4 color = frac(floor(color_16 / float4(1.0, 32.0, 1024.0, 32768.0)) / 32.0);

		color = color * In.v_color;
		float4x4 dither = float4x4(
			-4.0,  +0.0,  -3.0,  +1.0,
			+2.0,  -2.0,  +3.0,  -1.0,
			-3.0,  +1.0,  -4.0,  +0.0,
			+3.0,  -1.0,  +2.0,  -2.0) / 255.0;
		int2 dc = int2(frac(coord.xy / 4.0) * 4.0);
		color.xyz += dither[dc.x][dc.y] * In.v_texcoord.w;

		return color;
	}
#endif
