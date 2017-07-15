#pragma once

#include <vector>

//vulkan definitions
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan\vulkan.h>

#include "Graphics.h"
#include "CommandPool.h"

enum CommandBufferType
{
	Graphics = 0,
	Compute = 1,
	Transfer = 2,
	Sparse = 3
};

class CommandBuffer
{
public:
	CommandBuffer(CommandBufferType bufferType, VkCommandBufferLevel bufferLevel);
	~CommandBuffer();

	VkCommandBuffer GetVKCommandBuffer() const { return vkCommandBuffer; }
	VkSubmitInfo GetSubmitInfo() const { return submitInfo; }

	//Begin recording of the buffer
	void BeginRecording();

	//End the recording of the buffer
	void EndRecording();

	//End the recording of the buffer
	void ResetBuffer();

	//TODO: How the fuck do I want to do this?
	void AddWaitSemaphore(VkSemaphore semaphore);
	//TODO: How the fuck do I want to do this?
	void AddSignalSemaphore(VkSemaphore semaphore);


private:
	VkCommandBuffer vkCommandBuffer;
	VkSubmitInfo submitInfo;
	VkCommandBufferBeginInfo beginInfo;

	CommandPool* pCommandPool;

	std::vector<VkSemaphore> waitSemaphores;
	std::vector<VkSemaphore> signalSemaphores;
};
