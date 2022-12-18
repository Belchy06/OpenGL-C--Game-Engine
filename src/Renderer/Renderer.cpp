#include "Renderer.h"

void Renderer::Prepare()
{
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(RawModel InModel)
{
	glBindVertexArray(InModel.GetVaoId());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, InModel.GetVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}