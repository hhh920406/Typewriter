float diffuse = dot( normal, lVector );
if ( diffuse > uBorder) {
    diffuse = 1.0;
} else {
    diffuse = 0.5;
}