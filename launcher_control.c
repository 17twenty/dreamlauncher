#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LAUNCHER_NODE           "/dev/launcher0"
#define LAUNCHER_FIRE           0x10
#define LAUNCHER_STOP           0x20
#define LAUNCHER_UP             0x02
#define LAUNCHER_DOWN           0x01
#define LAUNCHER_LEFT           0x04
#define LAUNCHER_RIGHT          0x08
#define LAUNCHER_UP_LEFT        (LAUNCHER_UP | LAUNCHER_LEFT)
#define LAUNCHER_DOWN_LEFT      (LAUNCHER_DOWN | LAUNCHER_LEFT)
#define LAUNCHER_UP_RIGHT       (LAUNCHER_UP | LAUNCHER_RIGHT)
#define LAUNCHER_DOWN_RIGHT     (LAUNCHER_DOWN | LAUNCHER_RIGHT)

static void launcher_cmd(int fd, int cmd)
{
        int retval = 0;

        retval = write(fd, &cmd, 1);
        if (retval < 0) {
                fprintf(stderr, "Could not send command to " LAUNCHER_NODE
                        " (error %d)\n", retval);
        } else if (LAUNCHER_FIRE == cmd) {
                usleep(5000000);
        }
}

static void launcher_usage(char *name)
{
        fprintf(stderr, "Usage: %s [-mfslrudh] [-t <msecs>]\n"
                        "\t-m\tmissile launcher [" LAUNCHER_NODE "]\n"
                        "\t-f\tfire\n"
                        "\t-s\tstop\n"
                        "\t-l\tturn left\n"
                        "\t-r\tturn right\n"
                        "\t-u\tturn up\n"
                        "\t-d\tturn down\n"
                        "\t-t\tspecify duration to wait before sending STOP in milliseconds\n"
                        "\t-h\tdisplay this help\n\n"
                        "Notes:\n"
                        "\tIt is possible to combine the directions of the two axis, e.g.\n"
                        "\t'-lu' send_cmds the missile launcher up and left at the same time.\n"
                        "" , name);
        exit(1);
}


int main(int argc, char **argv)
{
        char c;
        int fd;
        int cmd = LAUNCHER_STOP;
        char *dev = LAUNCHER_NODE;
        unsigned int duration = 500;

        if (argc < 2) {
                launcher_usage(argv[0]);
        }

        while ((c = getopt(argc, argv, "mlrudfsht:")) != -1) {
                switch (c) {
                case 'm':
                        dev = optarg;
                        break;
                case 'l':
                        cmd = LAUNCHER_LEFT;
                        break;
                case 'r':
                        cmd = LAUNCHER_RIGHT;
                        break;
                case 'u':
                        cmd = LAUNCHER_UP;
                        break;
                case 'd':
                        cmd = LAUNCHER_DOWN;
                        break;
                case 'f': 
                        cmd = LAUNCHER_FIRE;
                        break;
                case 's':       
                        cmd = LAUNCHER_STOP;
                        break;
                case 't':
                        duration = strtol(optarg, NULL, 10);
                        fprintf(stdout, "Duration set to %d\n", duration);
                        break;
                default:
                        launcher_usage(argv[0]);
                }
        }

        fd = open(dev, O_RDWR);
        if (fd == -1) {
                perror("Couldn't open file: %m");
                exit(1);
        }
        launcher_cmd(fd, cmd);
        usleep(duration * 1000);
        launcher_cmd(fd, LAUNCHER_STOP);
        close(fd);
        return EXIT_SUCCESS;
}

