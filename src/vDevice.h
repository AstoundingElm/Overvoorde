#pragma once
#include "defines.h"
#include "darray.h"
#include "strings.h"
#include "logger.h"
typedef struct
{
    VkInstance instance;
   const VkAllocationCallbacks *allocator;
VkDebugUtilsMessengerEXT debug_messenger;
} VulkInstance;

void printInstanceExtensions();

void createInstance();
void destroyInstan();

void destroyDebuggerDevice();
void destroyVulkHandles();
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