function createStairs() {
    var stepMaterialVertical = new THREE.MeshLambertMaterial( { 
        color: 0xA85F35 
    } );
    var stepMaterialHorizontal = new THREE.MeshLambertMaterial( { 
        color: 0xBC7349 
    } );
    var stepWidth = 500;
    var stepSize = 200;
    var stepThickness = 50;
    var verticalStepHeight = stepSize;
    var horizontalStepDepth = stepSize*2;
    var stepHalfThickness = stepThickness/2;
    var stepVertical = new THREE.CubeGeometry(stepWidth, verticalStepHeight, stepThickness);
    var stepHorizontal = new THREE.CubeGeometry(stepWidth, stepThickness, horizontalStepDepth);
    var stepMesh;
    for (var i = 0; i < 6; ++i)
    {
        stepMesh = new THREE.Mesh(stepVertical, stepMaterialVertical);
        stepMesh.position.x = 0;
        stepMesh.position.y = i * (verticalStepHeight + stepThickness) + verticalStepHeight/2;
        stepMesh.position.z = i * (horizontalStepDepth - stepThickness);
        scene.add(stepMesh);
        stepMesh = new THREE.Mesh(stepHorizontal, stepMaterialHorizontal);
        stepMesh.position.x = 0;
        stepMesh.position.y = i * (verticalStepHeight + stepThickness) + stepThickness/2 + verticalStepHeight;
        stepMesh.position.z = i * (horizontalStepDepth - stepThickness) + horizontalStepDepth/2 - stepHalfThickness;
        scene.add(stepMesh);
    }
}

