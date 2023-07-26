export module apto.Graphics;

export namespace apto
{
	class __declspec(dllexport) IGraphicsEngine
	{
	public:
		virtual void Init() noexcept = 0;
		virtual void Finit() noexcept = 0;
		virtual void Render() noexcept = 0;
		virtual void BeginFrame() noexcept = 0;
		virtual void EndFrame() noexcept = 0;
		virtual void SetClearColor(float r, float g, float b, float a) noexcept = 0;
		virtual void Clear() noexcept = 0;
		virtual void DrawIndexed(unsigned int count) noexcept = 0;
		static IGraphicsEngine* Create() noexcept;
	};
}