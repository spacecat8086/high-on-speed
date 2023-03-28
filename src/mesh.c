#include "mesh.h"

VECTOR2 carMesh[CAR_VERTICES] = {
    // Car Body 0 - 15
    {36.0f, 12.0f},
    {30.0f, 16.0f},
    // Mirror
    {6.0f, 16.0f},
    {4.0f, 20.0f},
    {0.0f, 20.0f},
    {3.0f, 16.0f},

    {-30.0f, 16.0f},
    {-40.0f, 13.0f},
    
    {-40.0f, -13.0f},
    {-30.0f, -16.0f},
    // Mirror
    {3.0f, -16.0f},
    {0.0f, -20.0f},
    {4.0f, -20.0f},
    {6.0f, -16.0f},
    
    {30.0f, -16.0f},
    {36.0f, -12.0f},
    // Windshield 16 - 23
    {12.0f, 5.0f},
    {9.0f, 13.0f},
    {-1.0f, 9.0f},
    {1.0f, 4.0f},
    
    {1.0f, -4.0f},
    {-1.0f, -9.0f},
    {9.0f, -13.0f},
    {12.0f, -5.0f},
    // Right Window 24 - 27
    {6.0f, 14.0f},
    {-20.0f, 14.0f},
    {-16.0f, 10.0f},
    {-3.0f, 10.0f},
    // Left Window 28 - 31
    {6.0f, -14.0f},
    {-20.0f, -14.0f},
    {-16.0f, -10.0f},
    {-3.0f, -10.0f},
    // Rear Window 32 - 37
    {-19.0f, 9.0f},
    {-23.0f, 13.0f},
    {-30.0f, 10.0f},
    
    {-30.0f, -10.0f},
    {-23.0f, -13.0f},
    {-19.0f, -9.0f}
};

VECTOR2 carColMask[CAR_COLLISION_VERTICES] = {
    {35.0f, 15.0f},
    {-39.0f, 15.0f},
    {-39.0f, -15.0f},
    {35.0f, -15.0f}
};

VECTOR2 treeMesh[TREE_VERTICES] = {
    {40.0f, 4.0f},
    {21.0f, -38.0f},
    {-35.0f, -33.0f},
    {-44.0f, 12.0f},
    {5.0f, 34.0f},
    
    {26.0f, 6.0f},
    {18.0f, -26.0f},
    {-16.0f, -30.0f},
    {-32.0f, 0.0f},
    {-6.0f, 22.0f},
    
    {14.0f, 8.0f},
    {16.0f, -16.0f},
    {-4.0f, -25.0f},
    {-18.0f, -5.0f},
    {-12.0f, 10.0f}
};

VECTOR2 treeColMask[TREE_COLLISION_VERTICES] = {
    {14.0f, 8.0f},
    {16.0f, -16.0f},
    {-4.0f, -25.0f},
    {-18.0f, -5.0f},
    {-12.0f, 10.0f}
};

/*
POLYGON treePolygons[TREE_POLYGONS] = {
    {5, {0, 1, 2, 3, 4}, {0, 63, 0}},
    {5, {5, 6, 7, 8, 9}, {0, 91, 0}},
    {5, {10, 11, 12, 13, 14}, {0, 127, 0}}
};
*/

VECTOR2 dirtRoadMesh[DIRTROAD_FRAGMENTS] = {
    { 100.0f, 50.0f },
    { 250.0f, 50.0f },
    { 300.0f, 75.0f },
    { 325.0f, 125.0f },
    { 325.0f, 175.0f },
    { 300.0f, 225.0f },
    { 250.0f, 250.0f },
    { 150.0f, 250.0f },
    { 100.0f, 200.0f },
    { 75.0f, 115.0f },

    { 100.0f, 50.0f },
    { 70.0f, 30.0f },
    { 20.0f, 50.0f },
    { -120.0f, 60.0f },
    { -220.0f, 30.0f },
    { -300.0f, 40.0f },
    { -340.0f, 70.0f },
    { -370.0f, 90.0f },
    { -400.0f, 85.0f },
    { -440.0f, 50.0f },
    
    { -450.0f, -30.0f },
    { -445.0f, -120.0f },
    { -455.0f, -200.0f },
    { -450.0f, -240.0f },
    { -400.0f, -280.0f },
    { -320.0f, -310.0f },
    { -220.0f, -320.0f },
    { -130.0f, -305.0f },
    { -35.0f, -285.0f },
    { 15.0f, -270.0f },
    
    { 85.0f, -290.0f },
    { 130.0f, -300.0f },
    { 240.0f, -285.0f },
    { 305.0f, -295.0f },
    { 425.0f, -285.0f },
    { 540.0f, -290.0f },
    { 650.0f, -275.0f },
    { 740.0f, -280.0f },
    { 810.0f, -250.0f },
    { 840.0f, -220.0f },

    { 850.0f, -170.0f },
    { 820.0f, -120.0f },
    { 750.0f, -105.0f },
    { 625.0f, -110.0f },
    { 525.0f, -120.0f },
    { 470.0f, -100.0f },
    { 430.0f, -70.0f },
    { 395.0f, -10.0f },
    { 360.0f, 60.0f },
    { 325.0f, 140.0f },
};