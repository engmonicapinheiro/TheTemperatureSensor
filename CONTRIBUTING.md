# Onboarding

# Development Environment Setup

1. Checkout the project from Github
```
git clone git@github.com:engmonicapinheiro/TheTemperatureSensor.git
```

2. Install mise (cross-platform tool manager)
   - macOS/Linux:
     ```shell
     curl https://mise.run | sh
     ```
   - Or follow instructions at: https://mise.jdx.dev/getting-started.html

3. Import GNU keyring for GPG verification (required before installing make)
   - macOS/Linux:
     ```shell
     curl -s https://ftp.gnu.org/gnu/gnu-keyring.gpg | gpg --import
     ```

> [!Note:]
> These instructions were only tried on macOS Tahoe 26.1. So, your mileage may vary.
> Please add your experience and feedback regarding the setup process to improve these instructions.

4. Install project dependencies
```shell
mise install
```

5. Build the project
```shell
make all
```

6. Available Make tasks:
   - `make clean` - Remove all generated files
   - `make compile` - Compile the main.c file to main.elf
   - `make gen-asm` - Generate assembly file (main.s)
   - `make all` - Clean, compile, and generate assembly
   - `make graph.dot` - Generate Makefile dependency graph (dot format)
   - `make graph.png` - Generate Makefile dependency graph (PNG image)

7. Install CUBE IDE (for flashing to hardware)
   1. head over to https://www.st.com/en/development-tools/stm32cubeide.html
   2. download the latest version
   3. install it

8. Import and run the project in CUBE IDE
   1. open CUBE IDE
   2. create a new workspace (location is unimportant)
   3. import the project
      1. File -> Open Projects from File System
      2. Select import source: `<path/to/the/cloned/project/TheTemperatureSensor`
      3. Press Finish

>         -   Output
>             -   Load the code from the IDE into the chip and see the LEDs flashing
>             -   Change something and confirm the change gets applied to the chip

### Download datasheet and ref manual of STM32L031K6T6
>         -   Output
>             -   Put the necessary information to start in the project into the CONTRIBUTING.md
