#include "DeferredRenderPass.h"



DeferredRenderPass::DeferredRenderPass(uint32_t renderAreaWidth, uint32_t renderAreaHeight) : RenderPass(renderAreaWidth, renderAreaHeight)
{
	AddNewSubPass();

	//Main output
	VkAttachmentReference albedoOutput = AddColourAttachmentToCurrentSubpass(renderAreaWidth, renderAreaHeight, VkFormat::VK_FORMAT_R8G8B8A8_UNORM);
	VkAttachmentReference normalOutput = AddColourAttachmentToCurrentSubpass(renderAreaWidth, renderAreaHeight, VkFormat::VK_FORMAT_R8G8B8A8_UNORM);
	VkAttachmentReference positionOutput = AddColourAttachmentToCurrentSubpass(renderAreaWidth, renderAreaHeight, VkFormat::VK_FORMAT_R8G8B8A8_UNORM);

	AddDepthAttachmentToCurrentSubpass(renderAreaWidth, renderAreaHeight);

	//Finalize renderpass?
	CreateRenderPass();
}


DeferredRenderPass::~DeferredRenderPass()
{
}
