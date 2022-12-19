#include "Renderer.h"

void Renderer::Prepare()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 0, 0, 1);
}

void Renderer::Render(TexturedModel InModel)
{
	RawModel Model = InModel.GetRawModel();
	glBindVertexArray(Model.GetVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, InModel.GetModelTexture().GetTextureID());
	glDrawElements(GL_TRIANGLES, Model.GetVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}