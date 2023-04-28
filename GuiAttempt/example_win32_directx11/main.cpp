// Dear ImGui: standalone example application for DirectX 11
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "BoardGame.h"
#include "sorting.h"
#include <d3d11.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>


// Data
static ID3D11Device*            g_pd3dDevice = nullptr;
static ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
static IDXGISwapChain*          g_pSwapChain = nullptr;
static ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ChangeStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImColor(93, 127, 168, 255);
}
// Main code
int main(int, char**)
{
    vector<BoardGame*> storage;
    string line = "null";
    string fileName = "BGG_data_tab.txt";
    ifstream inFile(fileName);
    if (inFile.is_open())
    {
        getline(inFile, line);

        while (getline(inFile, line))
        {
            istringstream stream(line);
            //list all variables we need
            string sid;
            string name = "null";//
            string spublishDate = "";
            string sminPlayers = "";
            string smaxPlayers = "";
            string splayTime = "";
            string sminAge = "";
            string susersRated = "";
            string sratingAvg = "";
            string sBGGrank = "";
            string scomplexity = "";
            string sownedUsers = "";
            string mechanics = "null";
            string domains = "null";

            //reading in input and storing it into buffers
            getline(stream, sid, '\t');
            getline(stream, name, '\t');
            getline(stream, spublishDate, '\t');
            getline(stream, sminPlayers, '\t');
            getline(stream, smaxPlayers, '\t');
            getline(stream, splayTime, '\t');
            getline(stream, sminAge, '\t');
            getline(stream, susersRated, '\t');
            getline(stream, sratingAvg, '\t');
            getline(stream, sBGGrank, '\t');
            getline(stream, scomplexity, '\t');
            getline(stream, sownedUsers, '\t');
            getline(stream, mechanics, '\t');
            getline(stream, domains, '\t');

            //converting string input to correct data types
            int id = stoi(sid);
            int publishDate = stoi(spublishDate);
            int minPlayers = stoi(sminPlayers);
            int maxPlayers = stoi(smaxPlayers);
            int playTime = stoi(splayTime);
            int minAge = stoi(sminAge);
            int usersRated = stoi(susersRated);
            double ratingAvg = stod(sratingAvg);
            int BGGrank = stoi(sBGGrank);
            double complexity = stod(scomplexity);
            int ownedUsers = stoi(sownedUsers);

            //create a board game object
            BoardGame* game = new BoardGame(id, name, publishDate, minPlayers, maxPlayers, playTime, minAge, usersRated, ratingAvg, BGGrank, complexity, ownedUsers, mechanics, domains);

            storage.push_back(game);
        }

    }

    vector<BoardGame*> boardGames = storage;
    vector<BoardGame*> temp;

    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX11 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    bool noSort = true;
    bool shellBool = false;
    bool cocktailBool = false;
    int numPlayers = 0;
    vector<BoardGame*> topTen;
    auto started = std::chrono::high_resolution_clock::now();
    auto ended = std::chrono::high_resolution_clock::now();

    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        ChangeStyle();

        //tutorial code
        //ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->Size));
        static bool use_work_area = true;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        if (ImGui::Begin("Board Gamers", NULL)) {
            //declaring number of columns and size of each
            ImGui::Columns(3, NULL, true);
            ImGui::SetColumnOffset(1, ImGui::GetWindowWidth() / 3);


            //first column content
            {

                //========= PROCESS =========
                //create buttons for each thing
                //if button is pressed then it will perform deletion
                //copy paste code from the rudimentary main method

                //enter player count input textbox
                //ImGui::Text((boardGames[0]->name).c_str());
                ImGui::Text("Please enter player count: ");
                ImGui::InputInt("##playerCount", &numPlayers);
                if (numPlayers != 0){

                    for (auto it = boardGames.begin(); it != boardGames.end(); it++) {
                        if ((*it)->maxPlayers >= numPlayers) {
                            temp.push_back(*it);
                        }
                    }
                    boardGames.clear();
                    boardGames = temp;
                    temp.clear();

                }
                
                //length of game select one widget
                static int selectedOption = -1;
                ImGui::Text("Please enter desired length of gameplay: ");
                if (ImGui::Combo("##lengthCombo", &selectedOption, "N/A\0Short (0mins - 30mins)\0Medium (30mins - 1 hr)\0Long (1hr - 3 hrs)\0Extra Long (Multiple Days)")) {
                    switch (selectedOption)
                    {
                    case 0:
                        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
                        {
                            if ((*it)->playTime <= 30) // it->maxplayers is an issue
                            {
                                temp.push_back(*it);
                            }
                        }
                        boardGames.clear();
                        boardGames = temp;
                        temp.clear();
                        break;
                    case 1:
                        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
                        {
                            if ((*it)->playTime > 30 && (*it)->playTime <= 60) // it->maxplayers is an issue
                            {
                                temp.push_back(*it);
                            }
                        }
                        boardGames.clear();
                        boardGames = temp;
                        temp.clear();
                        break;
                    case 2:
                        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
                        {
                            if ((*it)->playTime < 30 && (*it)->playTime <= (60 * 4))
                            {
                                temp.push_back(*it);
                            }
                        }
                        boardGames.clear();
                        boardGames = temp;
                        temp.clear();
                        break;

                    case 3:

                        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
                        {
                            if ((*it)->playTime > (60 * 4))
                            {
                                temp.push_back(*it);
                            }
                        }
                        boardGames.clear();
                        boardGames = temp;
                        temp.clear();
                        break;
                    }
                   
                   
                   
                }

                //modern and vintage options ((normal buttons))
                ImGui::Text("Please choose either modern or vintage options: ");
                static int typeOption = -1;
                if (ImGui::Combo("##typeOption", &typeOption, "Modern Board Games ( > 2000s) \0 Vintage Board Games ( < 2000s)")) {
                    switch (typeOption) {
                    case 0:
                        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
                        {
                            if ((*it)->publishDate >= 2000)
                            {
                                temp.push_back(*it);
                            }
                        }
                        boardGames.clear();
                        boardGames = temp;
                        temp.clear();
                        break;
                    case 1:
                        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
                        {
                            if ((*it)->publishDate < 2000)
                            {
                                temp.push_back(*it);
                            }
                        }
                        boardGames.clear();
                        boardGames = temp;
                        temp.clear();
                        break;
                    }
                   
                }
                
                
                ImGui::Text("Please choose a sorting algorithm! : ");
                static int sortOption = -1;
                if (ImGui::Combo("##sortOption", &sortOption, "choose a sort\0Shell Sort \0Cocktail Sort")) {
                    switch (sortOption) {
                    case 0:
                        noSort = true;
                        shellBool = false;
                        cocktailBool = false;
                        break;
                    case 1:
                        noSort = false;
                        shellBool = true;
                        cocktailBool = false;
                        break;
                    case 2:
                        noSort = false;
                        shellBool = false;
                        cocktailBool = true;
                        break;
                    }
                }              

            }

            ImGui::NextColumn();
            //ImGui::SetCursorPosY(ImGui::GetWindowHeight());
            {
                //========= PROCESS =========
                //if both bool values are false then display
                //" please choose a sort!!"
                if (noSort) {
                    ImGui::Text("Please Choose a Sort!!");
                }
                if (shellBool == true) {
                   
               
                    /*for (auto it = boardGames.end() - 1; it != (boardGames.end() - 11); it--) {
                        topTen.push_back(*it);
                    }*/
                    ImGui::Text("it runs shell");
                    started = std::chrono::high_resolution_clock::now();
                    shellSort(boardGames);
                    ended = std::chrono::high_resolution_clock::now();
                    ImGui::Text("%d nanoseconds", std::chrono::duration_cast<std::chrono::nanoseconds>(ended - started).count());
                    //ImGui::Text((boardGames.at(0)->getName()).c_str());
                    
                }
                if (cocktailBool == true) {
                    
                    ImGui::Text("it runs cocktail");
                    started = std::chrono::high_resolution_clock::now();
                    cocktail(boardGames);
                    ended = std::chrono::high_resolution_clock::now();
                    ImGui::Text("%d nanoseconds", std::chrono::duration_cast<std::chrono::nanoseconds>(ended - started).count());
                }

               
                //if either sort bool value is true then
                //create buttons that display the name of the top
                //ten board games and their corresponding averages

                //for loop that creates buttons

                //very bottom will show the time that it takes to perform
                //said sort
            }

            ImGui::NextColumn();
            {
                //========= PROCESS =========
                //depending on which is easiest
                //if a button is clicked from the second column
                //display the info of the board game
                //name:
                //min players:
                //max players:
                //etc

            }
        }
        ImGui::End();
    


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        //{
        //    static float f = 0.0f;
        //    static int counter = 0;

        //    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        //    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //    ImGui::Checkbox("Another Window", &show_another_window);

        //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //        counter++;
        //    ImGui::SameLine();
        //    ImGui::Text("counter = %d", counter);

        //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        //    ImGui::End();
        //}

        //// 3. Show another simple window.
        //if (show_another_window)
        //{
        //    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        //    ImGui::Text("Hello from another window!");
        //    if (ImGui::Button("Close Me"))
        //        show_another_window = false;
        //    ImGui::End();
        //}

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != nullptr && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
