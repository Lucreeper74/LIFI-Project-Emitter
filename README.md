# Lifi Emitter Project Template

[![License: Apache2.0](https://img.shields.io/badge/License-Apache2.0-blue.svg)](https://www.apache.org/licenses/LICENSE-2.0)
[![Maintainer](https://img.shields.io/badge/Maintainer-Luc_Creeper74-orange)](https://github.com/Lucreeper74)

## Installation

The project can be installed and compiled with or without `CubeMX` on `STM32CubeIDE` or any other thirdparty IDE, especially `CLion` or `Visual Studio Code` (IDE used for the project creation) that have a dedicated plugin for **STM32** projects and `CMake` integration.

> [!IMPORTANT]
> This project already contain the OPAL_Driver as a `git` submodule!

### STM32CubeIDE Instructions :

Make sure to install correctly the `STM32CubeIDE`.

> [!IMPORTANT]
> In case you using `STM32CubeIDE 2.0.0` or above, you need to install `STM32CubeMX` apart!.<br>
> _See here for STM32CubeIDE and CubeMX installation : https://wiki.st.com/stm32mcu/wiki/STM32StepByStep:Step1_Tools_installation_

Make sure to install the latest version of `git`: <br>
_See here for Git installation : https://git-scm.com/book/en/v2/Getting-Started-Installing-Git_ 

Create a new **STM32** project for **STM32L073RZ** board in `CubeMX` and import it in `STM32CubeIDE`.<br>
_See here for Project creation : https://wiki.st.com/stm32mcu/wiki/STM32StepByStep:Step2_Blink_LED#Create_New_Project_using_STM32CubeMX_

In another directory, get the latest version of this repository using `git`: <br>

```bash
$ git clone https://github.com/Lucreeper74/LIFI-Project-Emitter
$ cd LIFI-Project-Emitter
```
_Or download manual project files using the Green "Code" button above and unzip the file._

Then, replace all the files this project to the STM32 Project previously created.
You can skip all the files that not present in the STM32 Project.


### Thirdparty IDE Instructions (Cmake Project) :

Make sure to install correctly the STM32 extension plugins provided by STMicroelectronics on Visual Studio Code:<br>
_See here for installation : https://www.st.com/content/st_com/en/campaigns/stm32-vs-code-extension-z11.html_

Or see here for the configuration to use STM32 project in Clion :<br>
_https://www.jetbrains.com/help/clion/embedded-stm32.html_

> [!IMPORTANT]
> If you use any other IDE, make sure it can handle CMake projects!

Get the latest version of this repository using `git`:
```bash
$ git clone https://github.com/Lucreeper74/LIFI-Project-Emitter
$ cd LIFI-Project-Emitter
```
_Or download manual project files using the Green "Code" button above and unzip the file._

> [!IMPORTANT]
> To configure the project for another STM32 MCU model, you need to change the definition in the [CMakeList.txt](https://github.com/Lucreeper74/LIFI-Project-Emitter/blob/main/CMakeLists.txt) in the `target_compile_definitions`.
> Please refer to the [OPAL_Driver Github](https://github.com/Lucreeper74/STM32_OPAL_Driver) page for supported STM32 MCU models

Import the project in the IDE and you're good to go!
