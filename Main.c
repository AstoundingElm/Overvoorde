#include <stdio.h>
#include "/home/peter/Desktop/vulkan/1.3.211.0/x86_64/include/vulkan/vulkan.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#define nullptr NULL
#define TUT5_MAX_LAYER_COUNT 20
#define TUT5_MAX_EXTENSION_COUNT 20
#define TUT5_MAX_LAYER_COUNT 20
#define TUT5_MAX_EXTENSION_COUNT 20
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

struct tut2_device
{
	VkDevice device;
	struct tut2_commands *command_pools;
	uint32_t command_pool_count;
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
   if(!result){
       return;
   }


}


static void print_layers_and_extensions(const char *indent, VkLayerProperties layers[TUT5_MAX_LAYER_COUNT], uint32_t layer_count,
		VkExtensionProperties extensions[TUT5_MAX_LAYER_COUNT + 1][TUT5_MAX_EXTENSION_COUNT], uint32_t extensions_count[TUT5_MAX_LAYER_COUNT + 1])
{
	/*
	 * First, let's print the extensions that are independent of layers.  Then, for each layer we will enumerate
	 * its own extensions as well.
	 */
	for (uint32_t j = 0; j < extensions_count[0]; ++j)
	{
		VkExtensionProperties *ext = &extensions[0][j];
		printf("%s* Extension: %s (versions: spec: 0x%08X)\n", indent, ext->extensionName, ext->specVersion);
	}
	for (uint32_t i = 0; i < layer_count; ++i)
	{
		VkLayerProperties *layer = &layers[i];
		printf("%s* Layer: %s (versions: spec: 0x%08X, implementation: 0x%08X)\n", indent, layer->layerName,
				layer->specVersion, layer->implementationVersion);
		printf("%s         %s\n", indent, layer->description);
		for (uint32_t j = 0; j < extensions_count[i + 1]; ++j)
		{
			VkExtensionProperties *ext = &extensions[i + 1][j];
			printf("%s  * Extension: %s (versions: spec: 0x%08X)\n", indent, ext->extensionName, ext->specVersion);
		}
	}
}

void tut5_print_layers_and_extensions(void)
{
	VkLayerProperties layers[TUT5_MAX_LAYER_COUNT];
	uint32_t layer_count = TUT5_MAX_LAYER_COUNT;

	VkExtensionProperties extensions[TUT5_MAX_LAYER_COUNT + 1][TUT5_MAX_EXTENSION_COUNT];
	uint32_t extensions_count[TUT5_MAX_LAYER_COUNT + 1];

	/*tut1_error res = get_layers_and_extensions(layers, &layer_count, extensions, extensions_count);
	if (tut1_error_is_error(&res))
		tut1_error_printf(&res, "Failed to enumerate instance layers and extensions\n");
	else if (tut1_error_is_warning(&res))
	*/
		printf("Much instance layers and extensions! Such Wow!\n");

	printf("Instance:\n");
	print_layers_and_extensions("", layers, layer_count, extensions, extensions_count);
}

void tut5_print_device_layers_and_extensions(struct tut1_physical_device *phy_dev)
{
	VkLayerProperties layers[TUT5_MAX_LAYER_COUNT];
	uint32_t layer_count = TUT5_MAX_LAYER_COUNT;

	VkExtensionProperties extensions[TUT5_MAX_LAYER_COUNT + 1][TUT5_MAX_EXTENSION_COUNT];
	uint32_t extensions_count[TUT5_MAX_LAYER_COUNT + 1];

/*	tut1_error res = get_device_layers_and_extensions(phy_dev->physical_device, layers, &layer_count, extensions, extensions_count);
	if (tut1_error_is_error(&res))
		tut1_error_printf(&res, "%s: Failed to enumerate device layers and extensions\n", phy_dev->properties.deviceName);
	else if (tut1_error_is_warning(&res))
	*/
		printf("%s: Much device layers and extensions! Such Wow!\n", phy_dev->properties.deviceName);

	printf("- Device %s:\n", phy_dev->properties.deviceName);
	print_layers_and_extensions("  ", layers, layer_count, extensions, extensions_count);
}

int main(){
GLFWwindow * window;
glfwInit();
glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
window = glfwCreateWindow(600, 800, "Vulkan", NULL, NULL);
while (!glfwWindowShouldClose(window)) {

glfwPollEvents();
//createInstance();
}

createInstance();
VkInstance vk;
	struct tut1_physical_device phy_devs[MAX_DEVICES];
	struct tut2_device devs[MAX_DEVICES];
	uint32_t dev_count = MAX_DEVICES;
/*for (uint32_t i = 0; i < dev_count; ++i)
	{
		res = tut5_setup(&phy_devs[i], &devs[i], VK_QUEUE_COMPUTE_BIT);
		
	}

	/* Let's print layers and extensions that we detected and are enabled */
	tut5_print_layers_and_extensions();
	for (uint32_t i = 0; i < dev_count; ++i)
	{
		printf("\n");
		tut5_print_device_layers_and_extensions(&phy_devs[i]);
	}
printf("yeah");

}
