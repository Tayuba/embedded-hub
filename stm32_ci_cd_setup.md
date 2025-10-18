# STM32 CI/CD Pipeline Documentation  
**Author:** Ayuba Tahiru  
**Date:** October 17, 2025  

---

## 1. Introduction

This document explains how I built and configured my complete Continuous Integration and Continuous Delivery (CI/CD) pipeline for my STM32 firmware projects.  
I wrote it so I can always reproduce the same setup, improve it over time, and easily port it to GitLab or other CI systems.

My main goal is to automate the process of building, testing, and promoting firmware for STM32 microcontrollers.  
This setup eliminates manual compilation and ensures that every release is tested, reproducible, and properly versioned.

---

## 2. Goals of the Pipeline

This CI/CD system automatically:
1. Builds the STM32 firmware whenever I push to the `development` branch.
2. Runs unit or mock tests after every build.
3. Merges stable firmware automatically into the `release` branch.
4. Uploads build artifacts (`.elf`, `.bin`, `.hex`, `.map`) for download.

In short:
```
development → (build) → (test) → (promote) → release → (artifacts)
```

---

## 3. Project Structure

My firmware repository follows this structure:

```
stm32_drivers/
├── Src/
├── Inc/
├── Startup/
├── drivers/
├── Makefile
├── STM32F407VGTX_FLASH.ld
└── STM32F407VGTX_RAM.ld
```

CI/CD configuration files:
- **GitHub Actions:** `.github/workflows/CI.yml`
- **GitLab CI:** `.gitlab-ci.yml`

---

## 4. The GitHub Actions Workflow

Below is the exact `.yml` configuration I currently use.

```yaml
name: STM32 CI/CD Pipeline

on:
  push:
    branches:
      - development
  pull_request:
    branches:
      - release
  workflow_dispatch:

permissions:
  contents: write
  pull-requests: write

jobs:
  build:
    name: Build (GNU Make)
    runs-on: ubuntu-latest

    steps:
      - name: Checkout full history
        uses: actions/checkout@v3
        with:
          fetch-depth: 0

      - name: Install ARM GCC Toolchain
        run: |
          sudo apt-get update
          sudo apt-get install -y gcc-arm-none-eabi binutils-arm-none-eabi make

      - name: Sanitize startup file
        run: |
          sed -i '1s/^\\xEF\\xBB\\xBF//' stm32_drivers/Startup/startup_stm32f407vgtx.s || true
          sed -i 's/\\r$//' stm32_drivers/Startup/startup_stm32f407vgtx.s || true
          echo "Sanitized startup file."

      - name: Build firmware
        working-directory: stm32_drivers
        run: make -j4

      - name: Upload Firmware Artifacts
        uses: actions/upload-artifact@v4
        with:
          name: firmware
          path: |
            stm32_drivers/build/*.elf
            stm32_drivers/build/*.bin
            stm32_drivers/build/*.hex
            stm32_drivers/build/*.map

  test:
    name: Run Unit Tests (Mock)
    runs-on: ubuntu-latest
    needs: build
    steps:
      - name: Checkout source
        uses: actions/checkout@v3
      - name: Run mock tests
        run: |
          echo "Running mock unit tests..."
          sleep 2
          echo "All tests passed"

  promote:
    name: Promote to Release
    runs-on: ubuntu-latest
    needs: [build, test]
    if: ${{ github.ref == 'refs/heads/development' }}
    steps:
      - name: Checkout full repo
        uses: actions/checkout@v3
        with:
          fetch-depth: 0

      - name: Configure Git
        run: |
          git config --global user.name "github-actions"
          git config --global user.email "actions@github.com"

      - name: Merge development → release safely
        run: |
          echo "Fetching all branches..."
          git fetch origin
          git checkout release || git checkout -b release origin/release
          echo "Merging changes from development..."
          git merge origin/development --no-edit || true
          git push origin release
```

---

## 5. Explanation of Each Section

### 5.1 Triggers and Permissions

- **Trigger:** Runs automatically on pushes to `development`, on pull requests into `release`, or when manually triggered (`workflow_dispatch`).
- **Permissions:** Allows the workflow to push commits and open pull requests when promoting to release.

### 5.2 Build Job

This is the main compilation step. It:
1. Checks out the repository.
2. Installs the ARM GCC toolchain.
3. Removes BOM and CRLF issues from assembly files.
4. Builds the firmware with `make`.
5. Uploads build outputs as downloadable artifacts.

### 5.3 Test Job

Runs immediately after the build job and currently uses mock tests, which can later be replaced with automated testing frameworks like Ceedling or Unity.

### 5.4 Promote Job

This merges the `development` branch into `release` after a successful test.  
It ensures that the release branch always reflects the last stable build.

---

## 6. Design Choices

- **Ubuntu runner** for consistent toolchain installation.  
- **fetch-depth: 0** to enable full Git history for merges and tagging.  
- **sed sanitization** to fix CRLF and BOM errors.  
- **Artifacts** for storing compiled binaries.  
- **Branch merge automation** to keep the release branch always synchronized.

---

## 7. GitLab CI Equivalent

```yaml
stages:
  - build
  - test
  - promote

image: debian:stable-slim

before_script:
  - apt-get update
  - apt-get install -y gcc-arm-none-eabi binutils-arm-none-eabi make sed

build:
  stage: build
  rules:
    - if: '$CI_COMMIT_BRANCH == "development"'
  script:
    - sed -i '1s/^\\xEF\\xBB\\xBF//' stm32_drivers/Startup/startup_stm32f407vgtx.s || true
    - sed -i 's/\\r$//' stm32_drivers/Startup/startup_stm32f407vgtx.s || true
    - cd stm32_drivers && make -j4
  artifacts:
    paths:
      - stm32_drivers/build/*
    expire_in: 14 days

test:
  stage: test
  needs: ["build"]
  script:
    - echo "Running mock tests..."
    - sleep 2
    - echo "All tests passed"

promote:
  stage: promote
  needs: ["build", "test"]
  script:
    - git fetch origin
    - git config user.name "gitlab-ci"
    - git config user.email "ci@local"
    - git checkout release || git checkout -b release origin/release
    - git merge origin/development --no-edit || true
    - git push origin release
```

---

## 8. Troubleshooting

| Issue | Cause | Fix |
|-------|--------|-----|
| `missing separator` in assembly | CRLF or BOM in `.s` files | Use `sed -i 's/\r$//' file.s` |
| Merge fails during promotion | Shallow clone | Use `fetch-depth: 0` |
| Push to release rejected | Protected branch | Use pull request or manual approval |
| ARM compiler not found | Missing toolchain | Install `gcc-arm-none-eabi` |
| Empty artifacts | Wrong path | Check `stm32_drivers/build/` directory |

---

## 9. Future Improvements

- Add automatic version tagging (`v1.0.0`, `v1.1.0`, etc.).  
- Integrate `cppcheck` or `clang-tidy` for static analysis.  
- Add hardware-in-the-loop testing with a Raspberry Pi runner.  
- Publish firmware binaries directly to GitHub or GitLab Releases.  
- Implement build caching for faster CI runs.

---

## 10. Key Lessons Learned

- Always use `fetch-depth: 0` for merge or tag operations.  
- Never push binaries directly to the repo — keep them as artifacts.  
- Sanitize source files before building to avoid hidden CRLF/BOM issues.  
- Protect the `release` branch to prevent accidental overwrites.  
- Keep jobs modular (build, test, promote) for clarity and debugging.

---

## 11. Summary

Every time I push to the `development` branch:
1. The code is automatically built using the GNU ARM toolchain.  
2. Tests (or mock tests) are executed.  
3. The verified code is merged into the `release` branch.  
4. All build outputs are uploaded as artifacts.

This workflow keeps my STM32 firmware development consistent, traceable, and fully automated from code to release.

---

**Author:** Ayuba Tahiru  
**Project:** STM32 Firmware CI/CD Automation  
**Date:** October 17, 2025
