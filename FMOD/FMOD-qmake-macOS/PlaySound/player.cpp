#include <QDebug>

#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    if (FMOD_RESULT result = FMOD::System_Create(&_sndSys); result != FMOD_OK) {
        qDebug() << "Error code: " << result;
    }

    _sndSys->init(32, FMOD_INIT_NORMAL, nullptr);
}

Player::~Player()
{
    if (_snd)
            _snd->release();

    if (_sndSys)
    {
        _sndSys->close();
        _sndSys->release();
    }
}

void Player::slotPlay()
{
    _sndSys->playSound(_snd, nullptr, false, &_ch);
}

void Player::slotResume()
{
    if (_ch)
        _ch->setPaused(false);
}

void Player::slotPause()
{
    if (_ch)
        _ch->setPaused(true);
}

QUrl const& Player::filePath() const
{
    return _filePath;
}

void Player::setFilePath(QUrl const& filePath)
{
    _filePath = filePath;

    qDebug() << _filePath.toLocalFile();
    _sndSys->createSound(_filePath.toLocalFile().toStdString().c_str(), FMOD_DEFAULT, nullptr, &_snd);

    emit filePathChanged(_filePath);
}

void Player::Update()
{
    _sndSys->update();
}
