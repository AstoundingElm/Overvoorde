#include <stdio.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#define debugBreak() __builtin_trap()
#define nullptr NULL
#define TUT5_MAX_EXTENSION_COUNT 20
#define TUT5_MAX_LAYER_COUNT 20
#define TUT1_MAX_QUEUE_FAMILY  20
#define MAX_DEVICES 10

VkInstance instance;

struct tut1_physical_device
{
	VkPhysicalDevice physical_device;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceMemoryProperties memories;

	VkQueueFamilyProperties queue_families[TUT1_MAX_QUEUE_FAMILY];
	uint32_t queue_family_count;
	bool queue_families_incomplete;
};




void createInstance(){

    VkApplicationInfo app_info = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "Vulkan Tutorial",
		.applicationVersion = 0x010000,
		.pEngineName = "Vulkan Tutorial",
		.engineVersion = 0x010000,
		.apiVersion = VK_API_VERSION_1_0,
	};

uint32_t glfwExtensionCount = 0;
 const char** glfwExtensions;

 glfwExtensions =
glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

VkInstanceCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &app_info,
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames = glfwExtensions,
        .enabledLayerCount = 0,
	};
   VkResult result = vkCreateInstance(&info, NULL, &instance);
   if(vkCreateInstance(&info, NULL, &instance)!= VK_SUCCESS){
       debugBreak();
   }


    VkLayerProperties layers[TUT5_MAX_LAYER_COUNT];
	 uint32_t layer_count;

   VkExtensionProperties extensions[TUT5_MAX_LAYER_COUNT + 1][TUT5_MAX_EXTENSION_COUNT];
   uint32_t extensioncount[TUT5_MAX_LAYER_COUNT + 1];
   extensioncount[0] = TUT5_MAX_EXTENSION_COUNT;
   vkEnumerateInstanceExtensionProperties(nullptr, &extensioncount[0], extensions[0]);
   
for (uint32_t j = 0; j < extensioncount[0]; ++j)
	{
		VkExtensionProperties *ext = &extensions[0][j];
		printf("%s* Extension: %s (versions: spec: 0x%08X)\n", "", ext->extensionName, ext->specVersion);
	}
	for (uint32_t i = 0; i < layer_count; ++i)
	{
		VkLayerProperties *layer = &layers[i];
		printf("%s* Layer: %s (versions: spec: 0x%08X, implementation: 0x%08X)\n", "", layer->layerName,
				layer->specVersion, layer->implementationVersion);
		printf("%s         %s\n", "", layer->description);
		for (uint32_t j = 0; j < extensioncount[i + 1]; ++j)
		{
			VkExtensionProperties *ext = &extensions[i + 1][j];
			printf("%s  * Extension: %s (versions: spec: 0x%08X)\n", "", ext->extensionName, ext->specVersion);
		}
	}


}

int main(){
GLFWwindow * window;
glfwInit();
glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
window = glfwCreateWindow(600, 800, "Vulkan", NULL, NULL);

while (!glfwWindowShouldClose(window)) {

glfwPollEvents();

}

createInstance();
glfwDestroyWindow(window);
glfwTerminate();
}
