function createCylinderFromEnds( material, radiusTop, radiusBottom, top, bottom, segmentsWidth, openEnded)
{
    segmentsWidth = (segmentsWidth === undefined) ? 32 : segmentsWidth;
    openEnded = (openEnded === undefined) ? false : openEnded;
    
    var cylAxis = new THREE.Vector3();
    cylAxis.subVectors(top, bottom);
    var length = cylAxis.length();
    
    var center = new THREE.Vector3();
    center.addVectors(top, bottom);
    center.divideScalar(2.0);

    var cylGeom = new THREE.CylinderGeometry( radiusTop, radiusBottom, length, segmentsWidth, 1, openEnded );
    var cyl = new THREE.Mesh( cylGeom, material );
    
    makeLengthAngleAxisTransform( cyl, cylAxis, center );

    return cyl;
}