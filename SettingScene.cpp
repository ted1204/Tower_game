#include <allegro5/allegro_audio.h>
#include <functional>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "SettingScene.hpp"
#include "Slider.hpp"



void SettingScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&SettingScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    Slider *sliderBGM, *sliderSFX;

    sliderBGM = new Slider(40 + halfW - 95, halfH - 50 - 2, 190, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&SettingScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH - 50, 255, 255, 255, 255, 0.5, 0.5));

    sliderSFX = new Slider(40 + halfW - 95, halfH + 50 - 2, 190, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&SettingScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH + 50, 255, 255, 255, 255, 0.5, 0.5));

    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void SettingScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopSample(bgmInstance);

}
void SettingScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void SettingScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void SettingScene::BGMSlideOnValueChanged(float value) {
/*
*/
    AudioHelper::BGMVolume = value;
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
}
void SettingScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}
