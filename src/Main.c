
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "darray.h"
#include "strings.h"
#define debugBreak() __builtin_trap()
#define nullptr NULL
#define TUT5_MAX_EXTENSION_COUNT 20
#define TUT5_MAX_LAYER_COUNT 20
#define TUT1_MAX_QUEUE_FAMILY  20
#define MAX_DEVICES 10

 VkAllocationCallbacks* allocator;


typedef char b8;
//const * validationLayers[] = { "VK_LAYER_KHRONOS_validation"};

#define DEBUG 1
#ifdef DEBUG
const bool enableValidationLayers = true;
#endif

VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data);

/*
b8 checkValidationLayerSupport(){

VkLayerProperties layers[TUT5_MAX_LAYER_COUNT];
	
	uint32_t  layer_count = TUT5_MAX_LAYER_COUNT;
    vkEnumerateInstanceLayerProperties(&layer_count, layers);

//printing stuff

	for (uint32_t i = 0; i < layer_count; ++i)
	{
		VkLayerProperties *layer = &layers[i];
		printf("%s* Layer: %s (versions: spec: 0x%08X, implementation: 0x%08X)\n", "", layer->layerName,
				layer->specVersion, layer->implementationVersion);
		printf("%s         %s\n", "", layer->description);
		
	}
	
return true;
}
*/


typedef struct{
VkInstance instance;
}VulkInstance;
VulkInstance Vinstance;


void printInstanceExtensions(){

   VkExtensionProperties extensions[TUT5_MAX_LAYER_COUNT + 1][TUT5_MAX_EXTENSION_COUNT];
   uint32_t extensioncount[TUT5_MAX_LAYER_COUNT + 1];
   extensioncount[0] = TUT5_MAX_EXTENSION_COUNT;
   
   vkEnumerateInstanceExtensionProperties(nullptr, &extensioncount[0], extensions[0]);
   
for (uint32_t j = 0; j < extensioncount[0]; ++j)
	{
		VkExtensionProperties *ext = &extensions[0][j];
		printf("%s* Extension: %s (versions: spec: 0x%08X)\n"," ", ext->extensionName, ext->specVersion);
	}

}

void createInstance(){
 allocator = 0;
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

// Validation layers.
    const char** required_validation_layer_names = 0;
    u32 required_validation_layer_count = 0;

// If validation should be done, get a list of the required validation layert names
// and make sure they exist. Validation layers should only be enabled on non-release builds.
#if defined(_DEBUG)
    printf("Validation layers enabled. Enumerating...\n");

    // The list of validation layers required.
    required_validation_layer_names = darray_create(const char*);
    darray_push(required_validation_layer_names, &"VK_LAYER_KHRONOS_validation");
    // NOTE: enable this when needed for debugging.
     //darray_push(required_validation_layer_names, &"VK_LAYER_LUNARG_api_dump");
    required_validation_layer_count = darray_length(required_validation_layer_names);

    // Obtain a list of available validation layers
    u32 available_layer_count = 0;
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, 0));
    VkLayerProperties* available_layers = darray_reserve(VkLayerProperties, available_layer_count);
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers));

    // Verify all required layers are available.
    for (u32 i = 0; i < required_validation_layer_count; ++i) {
        printf("Searching for layer: %s...\n", required_validation_layer_names[i]);
        b8 found = false;
        for (u32 j = 0; j < available_layer_count; ++j) {
            if (strings_equal(required_validation_layer_names[i], available_layers[j].layerName)) {
                found = true;
                printf("Found.\n");
                break;
            }
        }

        if (!found) {
            printf("Required validation layer is missing: %s\n", required_validation_layer_names[i]);
           // return false;
        }
    }
    printf("All required validation layers are present.\n");
#endif

   

VkInstanceCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &app_info,
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames = glfwExtensions,
        .enabledLayerCount = required_validation_layer_count,
		.ppEnabledLayerNames = required_validation_layer_names
	};


	
   VkResult result = vkCreateInstance(&info, NULL, &Vinstance.instance);
   if(vkCreateInstance(&info, allocator, &Vinstance.instance)!= VK_SUCCESS){
       debugBreak();
   }

printInstanceExtensions();
  
	u32 log_severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;  //|

	 VkDebugUtilsMessengerCreateInfoEXT debug_create_info = {
						
	.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
   .messageSeverity = log_severity,
    .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
   .pfnUserCallback = vk_debug_callback,

					   };

    PFN_vkCreateDebugUtilsMessengerEXT func =
        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Vinstance.instance, "vkCreateDebugUtilsMessengerEXT");
   // KASSERT_MSG(func, "Failed to create debug messenger!");
   // VK_CHECK(func(context.instance, &debug_create_info, context.allocator, &context.debug_messenger));
    printf("Vulkan debugger created.");
	
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
vkDestroyInstance(Vinstance.instance, nullptr);
glfwDestroyWindow(window);
glfwTerminate();
}


VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data) {
    switch (message_severity) {
        default:
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            printf(callback_data->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            printf(callback_data->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            printf(callback_data->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            printf(callback_data->pMessage);
            break;
    }
    return VK_FALSE;
}
