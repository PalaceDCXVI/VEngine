#pragma once

#include <vector>

//vulkan definitions
#ifndef VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include "vulkan\vulkan.h"

#include "glslang\Include\BaseTypes.h"
#include "glslang\Include\Common.h"
#include "glslang\Include\ShHandle.h"
#include "glslang\Include\intermediate.h"
#include "SPIRV\GlslangToSpv.h"

#include "Graphics.h"


class Shader
{
public:
	Shader(const char* filePath, VkShaderStageFlagBits shaderType);
	~Shader();

	VkShaderModule GetVKShaderModule() const { return vkShaderModule; }
	VkShaderStageFlags GetVKShaderStage() const { return vkShaderType; }

private:
	//Shader module
	VkShaderModule vkShaderModule;
	VkShaderStageFlags vkShaderType;

private:
	//Loads the file and places the text within the given string.
	void LoadShaderFromFile(const char* filePath, std::string &fileText);

	//Takes the text and creates a shader module
	bool CreateShaderModule(const char* fileText, VkShaderStageFlagBits shaderType);

private:
	bool GLSLtoSPV(const VkShaderStageFlagBits shader_type, const char *pshader, const char* shaderName, std::vector<unsigned int> &spirv);
	void init_resources(TBuiltInResource &Resources);
	EShLanguage FindLanguage(const VkShaderStageFlagBits shader_type);
	bool memory_type_from_properties(VkPhysicalDeviceMemoryProperties &memory_properties, uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex);
};

