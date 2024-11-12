#include "AnimationLib.h"
#include <DxLib.h>

AnimationLib::AnimationLib()
	: currentAnimHandle(-1)
	, isAnimating(false)
	, animSpeed(1.0f)
	, currentTime(0.0f)
{
}

AnimationLib::~AnimationLib()
{
}

void AnimationLib::LoadAnimation(const std::string& _animName, int _modelHandle, const std::string& _animFilePath)
{
	//int animHandle = MV1AttachAnim(_modelHandle,)
}

void AnimationLib::PlayAnimation(const std::string& _animName, bool _loop)
{
}

void AnimationLib::StopAnimation()
{
}

void AnimationLib::SetAnimationSpeed(float _speed)
{
}

void AnimationLib::Update(float _deltaTime, int _modelHandle)
{
}



//
//
//AnimationController::AnimationController()
//    : currentAnimHandle(-1), isAnimating(false), animSpeed(1.0f), currentTime(0.0f) {}
//
//AnimationController::~AnimationController() {
//    // 必要に応じてアニメーションのリソースを解放
//}
//
//void AnimationController::LoadAnimation(const std::string& animName, int modelHandle, const std::string& animFilePath) {
//    int animHandle = MV1AttachAnim(modelHandle, MV1LoadModel(animFilePath.c_str()));
//    animations[animName] = animHandle;
//}
//
//void AnimationController::PlayAnimation(const std::string& animName, bool loop) {
//    if (animations.count(animName) > 0) {
//        currentAnimHandle = animations[animName];
//        MV1SetAttachAnimTime(currentAnimHandle, 0.0f);
//        isAnimating = true;
//        MV1SetAttachAnimLoopFlag(currentAnimHandle, loop);
//    }
//}
//
//void AnimationController::StopAnimation() {
//    isAnimating = false;
//}
//
//void AnimationController::SetAnimationSpeed(float speed) {
//    animSpeed = speed;
//}
//
//void AnimationController::Update(float deltaTime, int modelHandle) {
//    if (isAnimating && currentAnimHandle != -1) {
//        currentTime += deltaTime * animSpeed;
//        MV1SetAttachAnimTime(modelHandle, currentAnimHandle, currentTime);
//    }
//}
//




/*使用例*/
//int modelHandle = MV1LoadModel("model.mv1");
//AnimationController animController;
//
//animController.LoadAnimation("Run", modelHandle, "runAnim.mv1");
//animController.PlayAnimation("Run", true);
//
//while (ProcessMessage() == 0) {
//	animController.Update(0.016f, modelHandle); // deltaTime 16ms
//	MV1DrawModel(modelHandle);
//}