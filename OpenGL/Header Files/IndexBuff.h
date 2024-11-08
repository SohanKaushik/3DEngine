#pragma once


class IndexBuff {

private:	
	unsigned int  ID;     //unique id for opengl buffers
	unsigned int m_Count;

public:
	IndexBuff(const unsigned int* data, unsigned int count);          // size * count makes whole thing
	~IndexBuff();


	void Bind() const;
	void Unbind() const;


	inline unsigned int GetCount() const { return m_Count; }
};