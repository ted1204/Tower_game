#ifndef SETTINGSCENE_HPP_INCLUDED
#define SETTINGSCENE_HPP_INCLUDED

#include <allegro5/allegro_audio.h>
#include "IScene.hpp"

class SettingScene final : public Engine::IScene {
private:
	float ticks;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
   	ALLEGRO_SAMPLE_ID bgmId;

public:
	explicit SettingScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
    void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif // SETTINGSCENE_HPP_INCLUDED
