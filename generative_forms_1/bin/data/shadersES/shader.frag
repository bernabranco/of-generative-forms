//////////////////////////////////
// Author Bernardo Branco 2020 //
////////////////////////////////

precision mediump float;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

uniform sampler2D u_tex0;
void main() {
  
    vec2 st = 1.0 - gl_FragCoord.xy/u_resolution.xy;
    vec2 coord = st*0.9;
    //coord = kaleido(coord*1.0);

   //DISTORT PIXEL COORDINATES
   for (int i = 0; i<5; i++){
    //coord.x += 0.028*noise(vec2(coord.x,coord.y)*u_mouse.x*0.05 + u_time*0.5);
    //coord.y += 0.028*noise(vec2(coord.x,coord.y)*u_mouse.y*0.05 + u_time*0.5);
}
    vec4 tex;
    tex = texture2D(u_tex0, st);
  
    vec3 color;
    color = vec3(tex.r,tex.g,tex.b);
  
   //OUTPUT COLOR
   gl_FragColor = vec4(color,1.);
}



