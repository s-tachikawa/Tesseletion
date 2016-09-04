// pack, unpack–½—ßŒQ
// floatX‚ğuintY‚ÉpackA‹y‚Ñ‚»‚Ì”½‘Î‚Éunpack‚·‚é–½—ßŒQ

// ƒJƒ‰[
uint PackColor( precise float4 unpackedInput )
{
    uint packedOutput;
    unpackedInput = min( max( unpackedInput, 0 ), 1 );	// NaN gets set to 0.
    unpackedInput *= 255;
    unpackedInput += 0.5;
    unpackedInput = floor( unpackedInput );
    packedOutput = ( ((uint)unpackedInput.r)      |
                    (((uint)unpackedInput.g)<< 8) |
                    (((uint)unpackedInput.b)<<16) |
                    (((uint)unpackedInput.a)<<24) );
    return packedOutput;
}
float4 UnpackColor( uint packedInput )
{
    precise float4 unpackedOutput;
    unpackedOutput.r = (float)  (packedInput      & 0x000000ff)  / 255;
    unpackedOutput.g = (float)(((packedInput>> 8) & 0x000000ff)) / 255;
    unpackedOutput.b = (float)(((packedInput>>16) & 0x000000ff)) / 255;
    unpackedOutput.a = (float)(((packedInput>>24) & 0x000000ff)) / 255;
    return unpackedOutput;
}

// –@ü
// ³‹K‰»‚³‚ê‚Ä‚¢‚é•K—v‚ª‚ ‚é
uint PackNormal( float3 norm )
{
	float3 n = 0.5 * ( 1.0 + norm );
	uint3 un = uint3( 1023.0 * n );
	return uint( un.x | ( un.y << 10 ) | ( un.z << 20 ) );
}
float3 UnpackNormal( uint norm )
{
	float3 res;
	res = float3( norm & 1023, norm&(1023 << 10), norm&(1023 << 20) ) *
			float3( 2.0 / 1023.0,
			2.0f / (1023.0 * 1024.0),
			2.0f / (1024.0 * 1024.0 * 1023.0) );
	res -= (1.0f).xxx;
	return res;
}

// •‚“®¬”“_
uint PackFloat2( float2 d )
{
    return ( f32tof16( d.x ) + ( f32tof16( d.y ) << 16 ) );
}
uint PackFloat2( float d0, float d1 )
{
    return ( f32tof16( d0 ) + ( f32tof16( d1 ) << 16 ) );
}
uint PackFloat( float d0 )
{
    return ( f32tof16( d0 ) );
}
float2 UnpackFloat2( uint d )
{
    return float2( f16tof32( d ), f16tof32( d >> 16 ) );
}
float UnpackFloat( uint d )
{
    return f16tof32( d );
}
