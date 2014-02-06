function createCapsule( material, radius, top, bottom, segmentsWidth, openTop, openBottom )
{
    segmentsWidth = (segmentsWidth === undefined) ? 32 : segmentsWidth;
    openTop = (openTop === undefined) ? false : openTop;
    openBottom = (openBottom === undefined) ? false : openBottom;

    var cylAxis = new THREE.Vector3();
    cylAxis.subVectors( top, bottom );
    var length = cylAxis.length();
    
    var center = new THREE.Vector3();
    center.addVectors( top, bottom );
    center.divideScalar( 2.0 );

    var cylGeom = new THREE.CylinderGeometry( radius, radius, length, segmentsWidth, 1, 1 );
    var cyl = new THREE.Mesh( cylGeom, material );
    
    makeLengthAngleAxisTransform( cyl, cylAxis, center );

    var capsule = new THREE.Object3D();
    var sphGeom = new THREE.SphereGeometry(radius, segmentsWidth, segmentsWidth/2);
    var sphere;
    capsule.add(cyl);
    if (!openTop) {
        sphere = new THREE.Mesh(sphGeom, material);
        sphere.position = top;
        capsule.add(sphere);
    }
    if (!openBottom) {
        sphere = new THREE.Mesh(sphGeom, material);
        sphere.position = bottom;
        capsule.add(sphere);
    }
    return capsule;
}