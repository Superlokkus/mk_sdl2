#include <cstdlib>

#include <mk_sdl2/sdl2_helpers.hpp>
#include <mk_sdl2/sdl2_audio_helper.hpp>

int main(int argc, char *argv[]) {
    mk::sdl2_cerr cerr{};
    if (argc < 2) {
        cerr << "Usage " << argv[0] << " <path_to_test_wav_file>\n";
        return EXIT_FAILURE;
    }

    try {
        mk::sdl2_event_helper event_helper{};
        mk::sdl2_audio_helper audio_helper{};
        mk::sdl2_cout cout{};

        event_helper.replace_quit_handler([&cout]() {
            cout << "Quiting!\n";
            std::exit(EXIT_SUCCESS);
        });

        audio_helper.play_wave(argv[1]);
        while (true)
            event_helper.update_ui();
    } catch (const std::exception &e) {
        cerr << "Exception main: " << e.what() << "\n";
        throw;
    }
}
