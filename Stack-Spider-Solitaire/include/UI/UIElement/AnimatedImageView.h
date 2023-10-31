#pragma once
#include "UI/UIElement/ImageView.h"
#include <functional>

namespace UIElement
{
	enum class AnimationType
	{
		FADE_IN,
		FADE_OUT,
	};

	class AnimatedImageView : public ImageView
	{
	  private:
		// Define a function pointer type for the callback function
		using CallbackFunction = std::function<void()>;

		// Store the callback function
		CallbackFunction callback_function = nullptr;

		void updateElapsedDuration();
		void handleAnimationProgress();
		void updateAnimation();

	  protected:
		const float default_animation_duration = 2.0f;

		AnimationType animation_type;
		float animation_duration;
		float elapsed_duration;
		sf::Clock clock;

		void setAnimationDuration(float duration);
		void setAnimationType(AnimationType type);

		void reset();

		void fadeIn();
		void fadeOut();

	  public:
		AnimatedImageView();
		~AnimatedImageView();

		void initialize() override;
		void initialize(sf::String texture_path, float image_width,
						float image_height, sf::Vector2f position);
		void update() override;
		void render() override;

		void playAnimation(AnimationType type, float duration,
						   CallbackFunction animation_end_callback);

		void registerCallbackFuntion(CallbackFunction animation_end_callback);
	};
} // namespace UIElement