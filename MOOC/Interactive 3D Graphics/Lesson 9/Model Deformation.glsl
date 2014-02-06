void main() {
    vec3 newPosition = position;
    newPosition.z = sqrt(uSphereRadius2 -
        newPosition.x * newPosition.x - newPosition.y * newPosition.y);
    newPosition.z -= sqrt(uSphereRadius2);
    gl_Position = projectionMatrix * modelViewMatrix * vec4( newPosition, 1.0 );
    vNormal = normalize( normalMatrix * normal );
    vec4 mvPosition = modelViewMatrix * vec4( newPosition, 1.0 );
    vViewPosition = -mvPosition.xyz;
}