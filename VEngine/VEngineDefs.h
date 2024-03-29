#pragma once

#ifndef EngineName
#define EngineName "V_ENGINE"
#endif // !EngineName
const int EngineVersion = 1;

#define ASSETSPATH "../Assets/"

//Queue priorities
const int GraphicsQueuePriority = 0;
const int PresentQueuePriority	= 0;
const int TransferQueuePriority = 0;
const int SparseQueuePriority	= 0;


//Uniforms
const int PerDrawUniformBufferSize = 512;
const int PerDrawUniformBinding = 1;
const int PerDrawUniformTextureBinding = 1; //TODO: find a place to put textures in the bindings. 