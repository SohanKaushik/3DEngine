#pragma once
#include "pch.h"

#include <render/framebuffer.h>

namespace render {
	

	class FrameBufferHandle {
		public:
			enum class FrameBufferType {
				Default,
				Color,
				Depth,
				GBuffer,
				MSAA,
				Stencil
			};

		private:
			struct FrameBufferEntry {
				int id;
				std::string name;
				FrameBufferType type;
				std::unique_ptr<Framebuffer> framebuffer;
			};

		public:
			static int AddFrameBuffer(std::unique_ptr<Framebuffer> framebuffer, FrameBufferType type, const std::string& name, int width, int height) {
				int _id = _index++;

				// create the buffer
				framebuffer->create_buffer(width, height);
				_stack[_id] = FrameBufferEntry{ _id, name, type, std::move(framebuffer) };
				_nameToID[name] = _id;

				return _id;
			}


			static void RemoveFrameBuffer(int id) {
				_stack.erase(id);
			}


			static Framebuffer* RetrieveFrameBuffer(const std::string& name) {
				auto it = _nameToID.find(name);
				if (it == _nameToID.end()) {
					std::cerr << name << " framebuffer has not found!";
					return nullptr;
				}
				return RetrieveFrameBuffer(it->second);
			}

			static Framebuffer* RetrieveFrameBuffer(int id) {
				auto it = _stack.find(id);
				if (it == _stack.end())
					return nullptr;
				return it->second.framebuffer.get();
			}


		private:
			static int _index;
			static std::unordered_map<std::string, int> _nameToID;
			static std::unordered_map<int, FrameBufferEntry> _stack;
	};


	

}