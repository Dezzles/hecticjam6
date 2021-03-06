#include "Psybrus.hlsl"


////////////////////////////////////////////////////////////////////////
// VS_INPUT
struct VS_INPUT
{
	float2 Position_		: POSITION;
	float2 TexCoord0_		: TEXCOORD0;
	float4 Colour_			: COLOR0;
};

////////////////////////////////////////////////////////////////////////
// VS_OUTPUT
struct VS_OUTPUT
{
	float4 Position_	: SV_POSITION;
	float2 TexCoord0_	: TEXCOORD0;
	float4 Colour_		: COLOR0;
};

////////////////////////////////////////////////////////////////////////
// PS_OUTPUT
struct PS_OUTPUT
{
	float4 Colour_		: SV_TARGET;
};


////////////////////////////////////////////////////////////////////////
// vertexMain
VS_OUTPUT vertexMain( VS_INPUT i )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.Position_ = mul( ClipTransform_, float4( i.Position_.xy, 0.0, 1.0 ) );
	o.TexCoord0_ = i.TexCoord0_;
	o.Colour_ = i.Colour_;
	return o;
}

////////////////////////////////////////////////////////////////////////
// pixelMain
PS_OUTPUT pixelMain( VS_OUTPUT i )
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	o.Colour_ = i.Colour_;
	return o;
}
