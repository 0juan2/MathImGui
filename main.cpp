//#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <math.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>
#include <Windows.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include <GLFW/glfw3native.h>
#include <string>
#include <vector>

#define GL_SILENCE_DEPRECATION

const char* glsl_version = "#version 330"; // Para OpenGL 3.3


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
int ventana(GLFWwindow* window){
	ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	bool show_demo_window = true;
    bool show_another_window = false;
	
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	double AproximacionPi = 0;
	static int counter = 1;
	float intervalo = 1.00f;          // Intervalo en segundos
	float tiempoAnterior = 0.0f; 
	bool Tiempo = 0;
	ImVec2 sizeImgui = ImVec2(400,400);
	std::vector<float> arr;
	int row1 = 0;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		   
		float tiempoActual = (float)glfwGetTime(); // Obtiene el tiempo actual en segundos
		
		{
			if (tiempoActual - tiempoAnterior >= intervalo) {
				tiempoAnterior = tiempoActual; 
				if (Tiempo){
					AproximacionPi += pow(-1,(counter+1)%2)/(2*counter-1);
					counter++;
					arr.push_back(AproximacionPi*4);
				}
			}
			ImGui::Begin("Pi Basilea", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
			ImGui::SetWindowSize(sizeImgui);
			ImGui::SetWindowPos("Pi Basilea", ImVec2(0, 0));
					
			ImGui::Checkbox("Tiempo",&Tiempo);
			if (ImGui::Button("Itera")){                            // Buttons return true when clicked (most widgets return true when edited/activated)
				AproximacionPi += pow(-1,(counter+1)%2)/(2*counter-1);
				counter++;
				arr.push_back(AproximacionPi*4);
				
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset")){                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter = 1;
				AproximacionPi = 0;
				arr.clear();
			}
			
			
			ImGui::Text("Pi va a valer: ");
			
			
			ImGui::Text("%.2f	", pow(-1,(counter+1)%2));     
			ImGui::SameLine();			
			ImGui::Text("iteracion = %i	", counter);
			ImGui::SameLine();
			ImGui::Text("Pi = %.6f", AproximacionPi*4);
			
			ImGui::Text("arr.size: %d",arr.size());
			{
			//ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, 10 * 1), ImVec2(FLT_MAX, 10 * 10)); 
			ImGui::BeginChild("Scrolling", ImVec2(ImGui::GetContentRegionAvail().x * 0.3f, 200));
			if (counter > 10){
				row1 = counter -11;
			}else{
				row1 = 0;
			}
			for (int row = row1; row < arr.size() ; row++)
				
				ImGui::Text("Pi %.8f", arr[row]);
				
			ImGui::EndChild();
			}
			ImGui::SameLine();
			{
				
				ImGui::BeginChild("Scrolling2", ImVec2(ImGui::GetContentRegionAvail().x , 300));
				ImGui::Text("Iteraciones de Pi");
				ImVec2 graph_size(ImGui::GetContentRegionAvail().x * 0.8f, 200);  // Ancho = 500, Alto = 200 (ajusta según lo que necesites)
				ImGui::PlotLines("Grafico 1", (float*)arr.data(), arr.size(), 0, nullptr, FLT_MAX, FLT_MAX, graph_size);

				//ImGui::PlotLines("1", (float*)arr.data(), arr.size());
				ImGui::EndChild();
			}
			//ImGui::Text("arr = %.4f",arr.data());
			
			ImGui::End();			 
		}
       
		ImGui::Render();    
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Color de fondo
        
		glClear(GL_COLOR_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwWaitEventsTimeout(1.0f - (tiempoActual - tiempoAnterior));
	}
	
	
    ImGui_ImplOpenGL3_Shutdown();  // Libera el backend de OpenGL
    ImGui_ImplGlfw_Shutdown();     // Libera el backend de GLFW
    ImGui::DestroyContext();       // Destruye el contexto principal de ImGui

    glfwDestroyWindow(window);     // Cierra la ventana de GLFW
    glfwTerminate();
	return 0;	
}

	

int main(){
	glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;


    // GL 3.0 + GLSL 130
    //const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); // Cambia a la versión que necesitas
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // O GLFW_OPENGL_COMPAT_PROFILE si necesitas compatibilidad

	
	int width = 400, height = 400;  
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Pi Basilea", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return 1;
	}
	glfwSetWindowPos(window, (mode->width - width) / 2, (mode->height - height) / 2);
    glfwSetWindowSize(window, width, height);
	
    glfwMakeContextCurrent(window);
    
	glfwSwapInterval(0);  // VSync
	
	glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
	glfwSetWindowSizeLimits(window, width, height, width, height);

    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
          
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
	
	HICON hIcon = (HICON)LoadImage(NULL, "icon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    if (hIcon) {
        HWND hwnd = glfwGetWin32Window(window); // Obtener el HWND de la ventana GLFW
        SetClassLongPtr(hwnd, GCLP_HICON, (LONG_PTR)hIcon); // Establecer el ícono
    
    }
	
	ventana(window);
	
	
	if (hIcon) {
        DestroyIcon(hIcon);
    }
	
}