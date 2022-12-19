#include "Renderer.h"

void Renderer::Prepare()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 0, 0, 1);
}

void Renderer::Render(RawModel InModel)
{
	glBindVertexArray(InModel.GetVaoId());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, InModel.GetVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}