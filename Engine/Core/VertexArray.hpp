#pragma once
#include "./Buffers.hpp"
#include <vector>
#include <climits>
#include <initializer_list>


namespace Engine
{
	/*
	Describes the layout of the vertex buffer
	*/
	struct VertexAttribLayout
	{
		int size;
		int type;
		int normalized;
		int stride;

		// utility function to help get the size of GL_FLOAT and other types
		const unsigned int getTypeSize() const
		{
			switch (type)
			{
			case GL_FLOAT:
			{
				return 4;
				break;
			}

			default:
			{
				return 4;
				break;
			}
			}
		}
	};
	/*
	Stores all of the buffers needed to create any sort of shape by managing
	The vertex and index buffers
	*/
	template<typename VertexType,
		typename IndexType>
		class VertexArray
	{
	public:
		VertexArray() noexcept
			:_vertexBuffer{}, _indexBuffer{}
		{};

		// VertexArray with just the Vertices
		VertexArray(VertexType* vertices, int verticiesSize,
			std::initializer_list<VertexAttribLayout> vertexLayout) noexcept
			:_vertexBuffer{ vertices, verticiesSize }, _indexBuffer{},
			_vertexLayout{vertexLayout}
		{}

		//Vertex buffer and index buffer included
		VertexArray(VertexType* vertices, int verticiesSize, IndexType* indexData, int indexSize,
			std::initializer_list<VertexAttribLayout> vertexLayout) noexcept
			:_vertexBuffer{ vertices, verticiesSize }, _indexBuffer{ indexData, indexSize },
			_vertexLayout{ vertexLayout }
		{}

		// I don't really want these and can't really think of a use case at the moment
		VertexArray(const VertexArray<VertexType, IndexType>& other) = delete;
		VertexArray<VertexType, IndexType>& operator=(const VertexArray<VertexType, IndexType>& other) = delete;
		VertexArray(VertexArray<VertexType, IndexType>&& other) noexcept
			:vertexArray{ other.vertexArray },
			_vertexBuffer{ std::move(other._vertexBuffer) },
			_indexBuffer{ std::move(other._indexBuffer) },
			_vertexLayout{ std::move(other._vertexLayout) }
		{
			other.vertex_array = 4294967295;
		};

		VertexArray<VertexType, IndexType>& operator=(VertexArray<VertexType, IndexType>&& other) noexcept
		{
			if (this != &other)
			{
				vertexArray = other.vertexArray;
				_vertexBuffer = std::move(other._vertexBuffer);
				_indexBuffer = std::move(other._indexBuffer);
				_vertexLayout = std::move(other._vertexLayout);


				// set this to the max to make sure that you don't delete the 
				// VertexArray when the temp object gets destroyed
				other.vertexArray = 4294967295;
			}

			return *this;
		}

		~VertexArray() noexcept
		{
			if (vertexArray != UINT_MAX)
			{
				glDeleteVertexArrays(1, &vertexArray);
			}
		};

		// Having a function for creating vertex array allows me to
		// add buffers after initializing the VAO
		void CreateVertexArray() noexcept
		{
			//create the vertex array and bind the buffers
			glGenVertexArrays(1, &vertexArray);
			glBindVertexArray(vertexArray);

			_vertexBuffer.bind();
			_vertexBuffer.setData();

			//set the layout of the vertex attribs
			unsigned int i = 0;
			unsigned int pointer = 0;
			for (auto& layout : _vertexLayout)
			{
				glVertexAttribPointer(i, layout.size, layout.type, layout.normalized, layout.stride, (void*)pointer);
				pointer += layout.size * layout.getTypeSize();
				glEnableVertexAttribArray(i);
				++i;
			}

			// Only create the index buffer if it exists
			if (_indexBuffer.isCreated())
			{
				_indexBuffer.bind();
				_indexBuffer.setData();
			}
		}

		void bind() const noexcept
		{
			glBindVertexArray(vertexArray);
		}

	private:
		unsigned int vertexArray = 0;
		std::vector<VertexAttribLayout> _vertexLayout;
		VertexBuffer<VertexType> _vertexBuffer;
		IndexBuffer<IndexType> _indexBuffer;
	};


}
