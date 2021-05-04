#include "main.h"

const LPWSTR window = L"HighOnSpeed";
const LPWSTR class = L"GameClass";
WNDCLASSEX wc = { sizeof (WNDCLASSEX), 0, WindowProc, 0, 0, NULL, NULL, NULL, NULL, NULL, class, NULL };
HWND hwnd;
HDC dc;
HDC backDC;
HBITMAP backBitmap;
HBRUSH backBrush;
HPEN invisiblePen;
RECT clientRect;

LARGE_INTEGER timerFreq;
float zoom = 2.0f;
int health = 100;

CAR car;
extern MATRIX3 globalTransform;
extern VECTOR2 carMesh[];
extern VECTOR2 carColMask[];
extern VECTOR2 treeMesh[];
extern VECTOR2 treeColMask[];
extern VECTOR2 dirtRoadMesh[];
extern ENTITY trees[];

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPWSTR pCmd, int nCmdShow)
{
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(0, class, window, STYLE, CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Can't create window", NULL, MB_ICONERROR);
    }
    ShowWindow(hwnd, nCmdShow);
    InitGraphics();

    MSG msg;
    int result = 1;
    LARGE_INTEGER lastUpdate;
    LARGE_INTEGER currentTime;
    float dt = 0.0f;

    QueryPerformanceFrequency(&timerFreq);
    QueryPerformanceCounter(&lastUpdate);

    while (result)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            result = GetMessage(&msg, NULL, 0, 0);
            DispatchMessage(&msg);
        }

        QueryPerformanceCounter(&currentTime);
        dt = (float) (currentTime.QuadPart - lastUpdate.QuadPart) / (float) timerFreq.QuadPart;
        lastUpdate.QuadPart = currentTime.QuadPart;

        if (health >= 0)
        {
            Update(&car, dt);
            TransformColMask(&car.visual);
            DetectCollisions();
        }
        Redraw();
    }
    return result;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE :
        InitCar();
        InitTrees();
        return 0;

    case WM_KEYUP :
        ReadKeys(wParam & 0xFF, FALSE);
        return 0;

    case WM_KEYDOWN :
        ReadKeys(wParam & 0xFF, TRUE);
        return 0;

    case WM_DESTROY :
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void InitGraphics()
{
    GetClientRect(hwnd, &clientRect);
    dc = GetDC(hwnd);

    backDC = CreateCompatibleDC(dc);
    backBitmap = CreateCompatibleBitmap(dc, clientRect.right, clientRect.bottom);
    SelectObject(backDC, backBitmap);

    backBrush = CreateSolidBrush(RGB(63, 127, 31));
    invisiblePen = GetStockObject(NULL_PEN);
}

void Redraw()
{
    if (car.v < 144.0f)
    {
        zoom = 2.0f;
    }
    else if (car.v < 576.0f)
    {
        zoom = 24.0f / sqrt(car.v);
    }
    else
    {
        zoom = 1.0f;
    }

    LoadIdentity(&globalTransform);
    Translate(
        &globalTransform, 
        clientRect.right / zoom / 2.0f - car.visual.pos.x,
        clientRect.bottom / zoom / 2.0f - car.visual.pos.y);
    Scale(&globalTransform, zoom, zoom);

    FillRect(backDC, &clientRect, backBrush);

    DrawDirtRoad(backDC, dirtRoadMesh, DIRTROAD_FRAGMENTS, 80);
    
    TransformMesh(&car.visual);
    DrawCar(backDC, car.visual.vertices);

    DrawTrees();    

    wchar_t textSpeed[32];
    wchar_t textHealth[32];
    wsprintf(textSpeed, L"speed: %d", (int) (fabs(car.v) * 0.216f));
    wsprintf(textHealth, L"health: %d", health);
    TextOut(backDC, 20, 20, textSpeed, wcslen(textSpeed));
    TextOut(backDC, 20, 40, textHealth, wcslen(textHealth));

    BitBlt(dc, 0, 0, clientRect.right, clientRect.bottom, backDC, 0, 0, SRCCOPY);
}
  
void ReadKeys(char key, BOOL state)
{
    switch (key)
    {
    case VK_UP :
        car.controls.up = state;
        break;
    
    case VK_DOWN :
        car.controls.down = state;
        break;

    case VK_LEFT :
        car.controls.left = state;
        break;

    case VK_RIGHT :
        car.controls.right = state;
        break;
    }
}

void DetectCollisions()
{
    for (int i = 0; i < TREE_COUNT; i++)
    {
        VECTOR2 dist = Diff(car.visual.pos, trees[i].pos);
        if (fabs(dist.x) < 100 && fabs(dist.y) < 100)
        {
            if (Collision(&car.visual, &trees[i]))
            {
                health -= (int) (fabs(car.v) / 5);
                if (health <= 0)
                {
                    MessageBox(NULL, L"You died!", window, MB_ICONWARNING | MB_OK | MB_APPLMODAL);
                    PostQuitMessage(0);
                }
                do {
                    car.visual.pos.x -= car.v / fabs(car.v) * cos(RAD(car.visual.angle)) * 1.0f;
                    car.visual.pos.y -= car.v / fabs(car.v) * sin(RAD(car.visual.angle)) * 1.0f;
                    TransformColMask(&car.visual);
                } 
                while (Collision(&car.visual, &trees[i]));
                car.v *= -0.2;
            }
        }
    }
}

void InitTrees()
{
    for (int i = 0; i < TREE_COUNT; i++)
    {
        trees[i].srcMesh = treeMesh;
        trees[i].srcCol = treeColMask;
        trees[i].vCount = TREE_VERTICES;
        trees[i].colCount = TREE_COLLISION_VERTICES;
        NewMesh(&trees[i]);
        NewColMask(&trees[i]);
        TransformColMask(&trees[i]);
    }
}

void InitCar()
{
    car.visual.srcMesh = carMesh;
    car.visual.srcCol = carColMask;
    car.visual.vCount = CAR_VERTICES;
    car.visual.colCount = CAR_COLLISION_VERTICES;
    NewMesh(&car.visual);
    NewColMask(&car.visual);
    car.visual.pos.x = 200.0f;
    car.visual.pos.y = 50.0f;
    car.visual.scale.x = 1.0f;
    car.visual.scale.y = 1.0f;
    car.visual.angle = 0.0f;
}

void DrawTrees()
{
    for (int i = 0; i < TREE_COUNT; i++)
    {
        TransformMesh(&trees[i]);
        DrawTree(backDC, trees[i].vertices);
    }
}

void DrawCar(HDC dc, PVECTOR2 mesh)
{
    POINT p[CAR_VERTICES];
    PPOINT currentPoint = p;
    ToPoint(p, mesh, CAR_VERTICES);

    SelectObject(dc, invisiblePen);
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(31, 31, 127));
    // Body
    Polygon(dc, currentPoint, 16);
    currentPoint += 16;
    // Windshield
    SetDCBrushColor(dc, RGB(191, 191, 213));
    Polygon(dc, currentPoint, 8);
    currentPoint += 8;
    // Side windows
    Polygon(dc, currentPoint, 4);
    currentPoint += 4;
    Polygon(dc, currentPoint, 4);
    currentPoint += 4;
    // Rear Window
    Polygon(dc, currentPoint, 6);
}

void DrawTree(HDC dc, PVECTOR2 mesh)
{
    POINT p[TREE_VERTICES];
    PPOINT currentPoint = p;
    ToPoint(p, mesh, TREE_VERTICES);

    SelectObject(dc, invisiblePen);
    SelectObject(dc, GetStockObject(DC_BRUSH));
    
    SetDCBrushColor(dc, RGB(0, 63, 0));    
    Polygon(dc, currentPoint, 5);
    currentPoint += 5;

    SetDCBrushColor(dc, RGB(0, 95, 0));    
    Polygon(dc, currentPoint, 5);
    currentPoint += 5;

    SetDCBrushColor(dc, RGB(0, 127, 0));    
    Polygon(dc, currentPoint, 5);
}

void DrawDirtRoad(HDC dc, PVECTOR2 ribbon, int fragments, float width)
{

    SelectObject(dc, invisiblePen);
    SelectObject(dc, GetStockObject(DC_BRUSH));    
    SetDCBrushColor(dc, RGB(159, 127, 63));  

    VECTOR2 oldEdges[2];

    for (int i = 0; i < fragments - 1; i++)
    {
        POINT rect[4];
        POINT triangles[4];
        VECTOR2 w = Mul((Normalize(Ortho(Diff(ribbon[i + 1], ribbon[i])))), width / 2);
        VECTOR2 vertices[4] = {
            Sum(ribbon[i], w),
            Diff(ribbon[i], w),
            Diff(ribbon[i + 1], w),
            Sum(ribbon[i + 1], w),
        };
        
        VECTOR2 empty[4] = {
            vertices[0],
            oldEdges[0],
            vertices[1],
            oldEdges[1]
        };

        CopyVector2(&oldEdges[0], vertices[2]);
        CopyVector2(&oldEdges[1], vertices[3]);

        for (int j = 0; j < 4; j++)
        {
            Apply(&globalTransform, &vertices[j]);
            Apply(&globalTransform, &empty[j]);
        }
        
        ToPoint(rect, vertices, 4);
        Polygon(dc, rect, 4);
        
        if (i > 0)
        {
            ToPoint(triangles, empty, 4);
            Polygon(dc, triangles, 4);
        }
    }
}