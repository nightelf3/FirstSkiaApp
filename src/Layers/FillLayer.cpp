#include "include/Layers/FillLayer.h"
#include "include/Utils/Shaders.h"
#include "include/Utils/Utils.h"
#include "include/Utils/ThemeUtils.h"
#include "include/Controls/Slider.h"
#include "include/Controls/Button.h"

namespace
{
	struct FillInput
	{
		SkScalar steps = 2.0f;
		SkScalar scale = 1.0f;
		SkScalar conical = 0.0f;
	};

	struct FXAAInput
	{
		SkVector scale;
	};

	sk_sp<SkShader> GetColorizer(SkScalar colors)
	{
		const int nColors = static_cast<int>(colors + 0.5f);
		SkBitmap bmp;
		bmp.allocN32Pixels(nColors, 1);

		SkColor* pixels = static_cast<SkColor*>(bmp.getPixels());
		for (int i = 0; i < nColors; i++)
		{
			const int nValue = (i * 255) / nColors;
			pixels[i] = SkColorSetARGB(255, nValue, nValue, nValue);
		}

		return bmp.asImage()->makeShader(SkSamplingOptions(SkFilterMode::kNearest));
	}

	sk_sp<SkShader> GetValueShader(FillType type)
	{
		SkString path;
		switch (type)
		{
		case FillType::Circular:
			path = "resources/shaders/Circular.sksl";
			break;

		case FillType::Conical:
			path = "resources/shaders/Conical.sksl";
			break;

		case FillType::Rectangular:
			path = "resources/shaders/Rectangular.sksl";
			break;

		default:
		case FillType::Linear:
			path = "resources/shaders/Linear.sksl";
			break;
		}

		auto [effect, error] = Shaders::LoadFromFile(path);
		return effect ? effect->makeShader(nullptr, nullptr, 0, nullptr, false) : nullptr;
	}

	sk_sp<SkShader> GetModeShader(FillMode type, SkScalar numSteps)
	{
		SkString path;
		sk_sp<SkData> dataInput;
		switch (type)
		{
		case FillMode::Mirror:
			dataInput = SkData::MakeWithCopy(&numSteps, sizeof(SkScalar));
			path = "resources/shaders/Mirror.sksl";
			break;

		case FillMode::Repeat:
			path = "resources/shaders/Repeat.sksl";
			break;

		default:
		case FillMode::Clamp:
			path = "resources/shaders/Clamp.sksl";
			break;
		}

		auto [effect, error] = Shaders::LoadFromFile(path);
		return effect ? effect->makeShader(dataInput, nullptr, 0, nullptr, false) : nullptr;
	}
}

FillLayer::FillLayer() : m_Container(ThemeUtils::GetRightContainerParams())
{
	SliderParams params;
	{
		auto&& effectContainer = m_Container.AddControl<ControlsContainer>(ThemeUtils::GetControlsContainerParams());

		params.m_Increment = 1.0f;
		params.m_Min = 2.0f;
		params.m_Max = 256.0f;
		params.m_Value = 10.0f;
		m_StepsSlider = effectContainer.lock()->AddControl<Slider>(params, SkString{ "Steps:" });

		params.m_Increment = 0.1f;
		params.m_Min = -10.0f;
		params.m_Max = 10.0f;
		params.m_Value = 1.0f;
		m_ScaleSlider = effectContainer.lock()->AddControl<Slider>(params, SkString{ "Scale:" });

		params.m_Increment = 0.1f;
		params.m_Min = -360.0f;
		params.m_Max = 360.0f;
		params.m_Value = 0.0f;
		m_RotateSlider = effectContainer.lock()->AddControl<Slider>(params, SkString{ "Rotate:" });

		params.m_Increment = 0.1f;
		params.m_Min = -0.9f;
		params.m_Max = 0.9f;
		params.m_Value = 0.0f;
		m_SkewSlider = effectContainer.lock()->AddControl<Slider>(params, SkString{ "Skew:" });

		effectContainer.lock()->AddControl<Button>([this]() {
			m_StepsSlider.lock()->SetValue(10.0f);
			m_ScaleSlider.lock()->SetValue(1.0f);
			m_RotateSlider.lock()->SetValue(0.0f);
			m_SkewSlider.lock()->SetValue(0.0f);
		}, SkString{ "Reset" });
	}

	{
		auto&& effectContainer = m_Container.AddControl<ControlsContainer>(ThemeUtils::GetControlsContainerParams());
		effectContainer.lock()->AddControl<Button>([this]() { m_FillType = FillType::Linear; }, SkString{ "Linear" });
		effectContainer.lock()->AddControl<Button>([this]() { m_FillType = FillType::Circular; }, SkString{ "Circular" });
		effectContainer.lock()->AddControl<Button>([this]() { m_FillType = FillType::Conical; }, SkString{ "Conical" });
		effectContainer.lock()->AddControl<Button>([this]() { m_FillType = FillType::Rectangular; }, SkString{ "Rectangular" });
	}

	{
		auto&& effectContainer = m_Container.AddControl<ControlsContainer>(ThemeUtils::GetControlsContainerParams());
		effectContainer.lock()->AddControl<Button>([this]() { m_FillMode = FillMode::Clamp; }, SkString{ "Clamp" });
		effectContainer.lock()->AddControl<Button>([this]() { m_FillMode = FillMode::Repeat; }, SkString{ "Repeat" });
		effectContainer.lock()->AddControl<Button>([this]() { m_FillMode = FillMode::Mirror; }, SkString{ "Mirror" });
	}

	{
		auto&& effectContainer = m_Container.AddControl<ControlsContainer>(ThemeUtils::GetControlsContainerParams());
		effectContainer.lock()->AddControl<Button>([this]() { m_FillAA = FillAA::None; }, SkString{ "None" });
		effectContainer.lock()->AddControl<Button>([this]() { m_FillAA = FillAA::Linear; }, SkString{ "Linear" });
		effectContainer.lock()->AddControl<Button>([this]() { m_FillAA = FillAA::FXAA; }, SkString{ "FXAA" });
	}

	{
		auto&& effectContainer = m_Container.AddControl<ControlsContainer>(ThemeUtils::GetControlsContainerParams());
		params.m_Increment = 1.0f;
		params.m_Min = 1.0f;
		params.m_Max = 5000.0f;
		params.m_Value = 1.0f;
		m_CycleSlider = effectContainer.lock()->AddControl<Slider>(params, SkString{ "Draw cycles:" });
	}
}

std::wstring FillLayer::GetTitle() const
{
	return L"Fill [" + std::to_wstring(static_cast<int>(m_Zoom * 100.0)) + L"%]";
}

void FillLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);
	const SkRect bounds = Utils::GetBounds(canvas);

	auto [effect, error] = Shaders::LoadFromFile(SkString{ m_FillAA == FillAA::Linear ? "resources/shaders/Fill_AA.sksl" : "resources/shaders/Fill.sksl" });
	if (effect)
	{
		SkAutoCanvasRestore guard(canvas, true);
		SkMatrix matWorld = SkMatrix::Scale(m_Zoom, m_Zoom);
		matWorld.postTranslate(bounds.centerX() + m_Pan.x(), bounds.centerY() + m_Pan.y());
		canvas->setMatrix(matWorld);

		constexpr SkScalar kRectSize = 600.0f;
		const SkRect rect = SkRect::MakeXYWH(-kRectSize * 0.5f, -kRectSize * 0.5f, kRectSize, kRectSize);
		SkMatrix localTrans = SkMatrix::RectToRect(SkRect::MakeWH(1.0f, 1.0f), rect)
			* SkMatrix::Translate(0.5f, 0.5f)
			* SkMatrix::Scale(0.5f, 0.5f);

		FillInput input;
		input.steps = std::floor(m_StepsSlider.lock()->GetValue() + 0.5f);
		input.scale = m_Zoom * m_ScaleSlider.lock()->GetValue();
		input.conical = m_FillType == FillType::Conical ? 1.0f : 0.0f;

		SkPaint paint;
		localTrans.postScale(m_ScaleSlider.lock()->GetValue(), m_ScaleSlider.lock()->GetValue());
		localTrans.postSkew(m_SkewSlider.lock()->GetValue(), m_SkewSlider.lock()->GetValue());
		localTrans.postRotate(m_RotateSlider.lock()->GetValue(), 0.5f, 0.5f);

		sk_sp<SkData> dataInput = SkData::MakeWithCopy(&input, sizeof(FillInput));
		sk_sp<SkShader> children[] = { GetColorizer(input.steps), GetValueShader(m_FillType), GetModeShader(m_FillMode, input.steps) };
		sk_sp<SkShader> colorizer = effect->makeShader(dataInput, children, 3, &localTrans, false);
		if (m_FillAA == FillAA::FXAA)
		{
			auto [effect, error] = Shaders::LoadFromFile(SkString{ "resources/shaders/FXAA.sksl" });

			FXAAInput input;
			input.scale = SkVector::Make(1.0f / m_Zoom, 1.0f / m_Zoom);
			sk_sp<SkData> dataInput = SkData::MakeWithCopy(&input, sizeof(FXAAInput));

			sk_sp<SkShader> children[] = { colorizer };
			colorizer = effect->makeShader(dataInput, children, 1, nullptr, false);
		}
		paint.setShader(colorizer);

		for (SkScalar i = 0; i < m_CycleSlider.lock()->GetValue(); i++)
			canvas->drawRect(rect, paint);
	}

	// draw controls
	m_Container.Draw(canvas, bounds);
}

bool FillLayer::ProcessKey(Key key, InputState state, ModifierKey modifiers)
{
	return m_Container.ProcessKey(key, state, modifiers);
}

bool FillLayer::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	if (m_Container.ProcessMouse(x, y, state, modifiers))
		return true;

	constexpr SkScalar kZoomValue = 0.75f;
	switch (state)
	{
	case InputState::kDown:
		m_MouseDown = true;
		m_ptMouse = SkPoint::Make(x, y);
		break;

	case InputState::kUp:
		m_MouseDown = false;
		break;

	case InputState::kMove:
		if (m_MouseDown)
		{
			m_Pan += SkPoint::Make(x - m_ptMouse.x(), y - m_ptMouse.y());
			m_ptMouse = SkPoint::Make(x, y);
		}
		break;

	case InputState::kZoomIn:
		if (m_Zoom < 10'000.0)
			m_Zoom /= kZoomValue;
		break;

	case InputState::kZoomOut:
		if (m_Zoom > 0.02)
			m_Zoom *= kZoomValue;
		break;

	default:
		return false;
	}

	return true;
}