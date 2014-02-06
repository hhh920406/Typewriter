function createHelix( material, radius, tube, radialSegments, tubularSegments, height, arc, clockwise )
{
    tubularSegments = (tubularSegments === undefined) ? 32 : tubularSegments;
    arc = (arc === undefined) ? 1 : arc;
    clockwise = (clockwise === undefined) ? true : clockwise;

    var helix = new THREE.Object3D();
    var top = new THREE.Vector3();
    var bottom = new THREE.Vector3(radius, -height / 2, 0);
    var sine_sign = clockwise ? 1 : -1;

    var openTop = false;
    var openBottom = false;
    var sphGeom = new THREE.SphereGeometry( tube, tubularSegments, tubularSegments/2 );
    for ( var i = 1; i <= arc*radialSegments ; i++ )
    {
        top.set( radius * Math.cos( i * 2*Math.PI / radialSegments ),
        height * (i/(arc*radialSegments)) - height/2,
        sine_sign * radius * Math.sin( i * 2*Math.PI / radialSegments ) );
        
        var capsule = createCapsule(material, tube, top, bottom, tubularSegments, openTop, openBottom);
        helix.add(capsule);
        openBottom = true;
        bottom.copy(top);
    }
    return helix;
}