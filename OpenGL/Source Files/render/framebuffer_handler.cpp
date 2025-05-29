#include "pch.h"
#include "framebuffer_handler.h"

namespace render {
	int FrameBufferHandle::_index = 0;
	std::unordered_map<std::string, int> FrameBufferHandle::_nameToID = {};
	std::unordered_map<int, FrameBufferHandle::FrameBufferEntry> FrameBufferHandle::_stack = {};

}