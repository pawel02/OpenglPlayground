#pragma once
#include <glad/glad.h>


/*
Wrappers for :
- Vertex Array Buffer
- Index Buffer
- Framebuffers
- Uniform buffers
*/

namespace Engine
{
template<typename T>
class VertexBuffer
{
public:

	VertexBuffer() = default;

	VertexBuffer(T* data, size_t dataSize) noexcept
		:_data{ data }, _dataSize{ dataSize }, _drawMethod{ GL_STATIC_DRAW }
	{
		glGenBuffers(1, &_buffer);
	};

	VertexBuffer(T* data, size_t dataSize, int drawMethod) noexcept
		:_data{ data }, _dataSize{ dataSize }, _drawMethod{ drawMethod }
	{
		glGenBuffers(1, &_buffer);
	};

	~VertexBuffer() = default;

	VertexBuffer(VertexBuffer&& other) noexcept
		:_buffer{ other._buffer },
		_drawMethod{ other._drawMethod },
		_data{ other._data },
		_dataSize{ other._dataSize }
	{}

	VertexBuffer& operator=(VertexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			_buffer = other._buffer;
			_drawMethod = other._drawMethod;
			_data = other._data;
			_dataSize = other._dataSize;
		}
		return *this;
	}

	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	};
	void setData()
	{
		glBufferData(GL_ARRAY_BUFFER, _dataSize, _data, _drawMethod);
	}

private:
	unsigned int _buffer;

	int _drawMethod;

	T* _data;
	size_t _dataSize;
};

template<typename T>
class IndexBuffer
{
public:
	IndexBuffer() noexcept 
		:_buffer{0},_data {nullptr}, 
		_dataSize{ 0 }, _drawMethod{ GL_STATIC_DRAW },
		_isCreated{false}
	{};

	IndexBuffer(T* data, size_t dataSize) noexcept
		:_data{ data }, _dataSize{ dataSize }, _drawMethod{ GL_STATIC_DRAW },
		_isCreated{ true }
	{
		glGenBuffers(1, &_buffer);
	}

	IndexBuffer(T* data, size_t dataSize, int drawMethod) noexcept
		:_data{ data }, _dataSize{ dataSize }, _drawMethod{ drawMethod },
		_isCreated{ true }
	{
		glGenBuffers(1, &_buffer);
	}

	~IndexBuffer() = default;

	IndexBuffer(IndexBuffer&& other) noexcept
		:_buffer{ other._buffer },
		_drawMethod{ other._drawMethod },
		_data{ other._data },
		_dataSize{ other._dataSize },
		_isCreated{other._isCreated }
	{}

	IndexBuffer& operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			_buffer = other._buffer;
			_drawMethod = other._drawMethod;
			_data = other._data;
			_dataSize = other._dataSize;
			_isCreated = other._isCreated;
		}
		return *this;
	}

	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
	}

	void setData()
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _dataSize, _data, _drawMethod);
	}

	bool isCreated() const noexcept { return _isCreated; }
private:
	unsigned int _buffer;
	bool _isCreated = false;

	int _drawMethod;

	T* _data;
	size_t _dataSize;
};

/*
Used for sharing data between shaders programs
*/
class UniformBuffer
{
public:
	UniformBuffer() = default;

	UniformBuffer(size_t dataSize) noexcept
		:_dataSize{ dataSize }, _drawMethod{ GL_STATIC_DRAW }
	{
		glGenBuffers(1, &_buffer);
		bind();
		glBufferData(GL_UNIFORM_BUFFER, _dataSize, NULL, _drawMethod);
	}

	UniformBuffer(size_t dataSize, int drawMethod) noexcept
		:_dataSize{ dataSize }, _drawMethod{ drawMethod }
	{
		glGenBuffers(1, &_buffer);
		bind();
		glBufferData(GL_UNIFORM_BUFFER, _dataSize, NULL, _drawMethod);
	}

	~UniformBuffer() = default;

	UniformBuffer(UniformBuffer&& other) noexcept
		:_buffer{ other._buffer },
		_drawMethod{ other._drawMethod },
		_dataSize{ other._dataSize }
	{}

	UniformBuffer& operator=(UniformBuffer&& other) noexcept
	{
		if (this != &other)
		{
			_buffer = other._buffer;
			_drawMethod = other._drawMethod;
			_dataSize = other._dataSize;
		}
		return *this;
	}

	void bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, _buffer);
	}

	void bindBufferBlock(unsigned int index)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, index, _buffer);
	}

	/*
	Sub the data into the uniform buffer,
	You will need to take aligned of the variables into account
	This was made to comply with std140 (aligned offset must be a multiple of 16)
	*/
	template<typename T>
	void subData(T* data, unsigned int offset, unsigned int size)
	{
		bind();
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	}

private:
	unsigned int _buffer;

	int _drawMethod;

	size_t _dataSize;
};

}