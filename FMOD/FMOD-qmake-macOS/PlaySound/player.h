#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QUrl>

#include <fmod/fmod.hpp>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    ~Player();

    QUrl const& filePath() const;
    void setFilePath(QUrl const&);

    void Update();

signals:

    void filePathChanged(QUrl const&);

public slots:
    void slotPlay();
    void slotResume();
    void slotPause();

private:
    FMOD::System *_sndSys = nullptr;
    FMOD::Sound *_snd = nullptr;
    FMOD::Channel *_ch = nullptr;

    QUrl _filePath;
    Q_PROPERTY(QUrl filePath WRITE setFilePath READ filePath NOTIFY filePathChanged)
};

#endif // PLAYER_H
