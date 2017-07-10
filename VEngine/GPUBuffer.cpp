#include "GPUBuffer.h"



GPUBuffer::GPUBuffer(VkBufferUsageFlags bufferUsage, void* data, uint64_t memorySize)
{
	// Create buffer handle //
	VkBufferCreateInfo bufferCI;
	bufferCI.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferCI.pNext = nullptr;
	bufferCI.flags = 0;
	bufferCI.size = memorySize; //size of the buffer in bytes
	bufferCI.usage = bufferUsage; //What the buffer actually is
	bufferCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE; //Not planning any concurrency currently.
	bufferCI.queueFamilyIndexCount = 0; //Used when sharingMode is set to concurrent
	bufferCI.pQueueFamilyIndices = NULL;

	const VkDevice logicalDevice = GraphicsSystem::GetSingleton()->GetLogicalDevice()->GetVKLogicalDevice();

	VkResult result;

	result = vkCreateBuffer(logicalDevice, &bufferCI, NULL, &vkBuffer);
	assert(result == VK_SUCCESS);

	//Fetch the memory requirements of the buffer
	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(logicalDevice, vkBuffer, &memRequirements);

	// Back the buffer handle with device memory //
	VkMemoryAllocateInfo bufferMemoryAI;
	bufferMemoryAI.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	bufferMemoryAI.pNext = NULL;
	bufferMemoryAI.allocationSize = bufferCI.size;
	bufferMemoryAI.memoryTypeIndex = FindMemoryType(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, memRequirements.memoryTypeBits);

	assert(bufferMemoryAI.memoryTypeIndex > -1);
	result = vkAllocateMemory(logicalDevice, &bufferMemoryAI, NULL, &vkMemory);
	assert(result == VK_SUCCESS);

	// Load the data into the buffer //
	vkBindBufferMemory(logicalDevice, vkBuffer, vkMemory, 0);

	void* deviceData;
	vkMapMemory(logicalDevice, vkMemory, 0, bufferCI.size, 0, &deviceData);
	memcpy(deviceData, data, (size_t)bufferCI.size);
	vkUnmapMemory(logicalDevice, vkMemory);
}


GPUBuffer::~GPUBuffer()
{
	const VkDevice logicalDevice = GraphicsSystem::GetSingleton()->GetLogicalDevice()->GetVKLogicalDevice();

	vkFreeMemory(logicalDevice, vkMemory, NULL);

	vkDestroyBuffer(logicalDevice, vkBuffer, NULL);
}

uint32_t GPUBuffer::FindMemoryType(uint32_t typeBits, VkFlags requirements_mask)
{
	const VkPhysicalDeviceMemoryProperties memory_properties = GraphicsSystem::GetSingleton()->GetPhysicalDevice()->GetPhysicalDeviceMemoryPropertiess();
	
	uint32_t typeIndex = -1;




	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < memory_properties.memoryTypeCount; i++) {
		if ((typeBits & 1) == 1) {
			// Type is available, does it match user properties?
			if ((memory_properties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask) {
				typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}
	// No memory types matched, return failure
	return typeBits;
}