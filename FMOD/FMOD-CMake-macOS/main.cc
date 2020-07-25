#include <iostream>
#include <cstdlib>

#include <unistd.h>
#include <time.h>

#include <fmod/fmod.hpp>

bool UserPressedEscKey() {
    return false;
}

bool NanoSleep(long nsec) {
    struct timespec req, rem;
    req.tv_sec = 0;  // seconds
    req.tv_nsec = nsec;  // nanoseconds
    return nanosleep(&req , &rem) >= 0;
}

int main(int argc, char *argv[])
{
    std::string cwd(getcwd(NULL,0));
    std::cout << "CWD is: " << cwd << std::endl;

    // Initialize FMOD:
    FMOD::System *sys;
    if (FMOD_RESULT result = FMOD::System_Create(&sys); result != FMOD_OK) {
        std::cout << "Error code: " << result << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "FMOD_VERSION: 0x" << std::hex << FMOD_VERSION << std::dec << std::endl;

    unsigned int version = 0;

    if (FMOD_RESULT result = sys->getVersion(&version); result != FMOD_OK) {
        std::cout << "Error code: " << result << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "getVersion: 0x" << std::hex << version << std::dec << std::endl;

    if (version < FMOD_VERSION) {
        printf("Error! FMOD version %08x required.\n", FMOD_VERSION);
        exit(0);
    }

    sys->init(32, FMOD_INIT_NORMAL, NULL);

    // Load and play a sound sample:
    FMOD::Sound *sound;
    // sys->createSound("83538__zgump__bell-0101.wav", FMOD_SOFTWARE, 0, &sound);
    sys->createSound("83538__zgump__bell-0101.wav", FMOD_DEFAULT, 0, &sound);

    FMOD::Channel *channel = nullptr;

    // sys->playSound(FMOD_CHANNEL_FREE, sound, 0, &channel);
    sys->playSound(sound, nullptr, false, &channel);

    // Main loop:
    while (!UserPressedEscKey()) {
        sys->update();
        NanoSleep(10);
    }

    // Shut down:
    sound->release();
    sys->close();
    sys->release();

    return EXIT_SUCCESS;
}
