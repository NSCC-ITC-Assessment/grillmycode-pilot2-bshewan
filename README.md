# GrillMyCode - Pilot #2

This repository contains fourteen GitHub Actions workflows that each analyse submitted code and generate comprehension questions using a different AI model. Unlike Pilot #1 — where a single action fired automatically on every push — the actions in this pilot are **triggered manually**, one at a time, so that the question output from each model can be observed and compared independently.

---

## Purpose of This Pilot

Building on Pilot #1, this pilot has two goals:

1. **Cross-model comparison** — Run the same submitted code through eleven different AI models and evaluate whether the quality, relevance, and depth of the generated questions varies meaningfully between models.
2. **Model selection** — Use the comparison results to identify which model(s) produce the most useful comprehension questions, informing which model(s) to use going forward. If there is a model that works particularly well or alternatively works particularly badly, it would be good to get that feedback.

Your feedback on question quality is highly valuable. Note any differences you observe between models — questions that feel generic, off-topic, or surprisingly insightful are all worth flagging. Feedback on workflow behaviour, output format, or anything else that feels off is equally welcome.

> **Note:** The code you submit does not need to be fully functional or have perfect syntax. Part of the purpose of this pilot is to observe what questions different models generate from realistic, work-in-progress code — so feel free to push incomplete code and see what happens.

---

## The Fourteen Actions

There are fourteen workflows, grouped by the API they call:

### GitHub Models

These four workflows call models hosted on **GitHub Models**:

| Workflow name | Model ID |
|---|---|
| GrillMyCode - Github Models - Codestral 2501 | `Codestral-2501` |
| GrillMyCode - Github Models - GPT 4.1 | `gpt-4.1` |
| GrillMyCode - Github Models - GPT 4o | `gpt-4o` |
| GrillMyCode - Github Models - Mistral Medium 2505 | `mistral-medium-2505` |

### OpenRouter

These ten workflows call models via **OpenRouter**:

| Workflow name | Model ID |
|---|---|
| GrillMyCode - OpenRouter - Claude Haiku 4.5 | `anthropic/claude-haiku-4.5` |
| GrillMyCode - OpenRouter - DeepSeek V4 Pro | `deepseek/deepseek-v4-pro` |
| GrillMyCode - OpenRouter - GLM 5 | `z-ai/glm-5` |
| GrillMyCode - OpenRouter - Google Gemini 3 Flash Preview | `google/gemini-3-flash-preview` |
| GrillMyCode - OpenRouter - Google Gemma 4 31B | `google/gemma-4-31b-it` |
| GrillMyCode - OpenRouter - GPT 5.1 Codex Mini | `openai/gpt-5.1-codex-mini` |
| GrillMyCode - OpenRouter - Minimax 2.7 | `minimax/minimax-m2.7` |
| GrillMyCode - OpenRouter - Qwen 3.6 Plus | `qwen/qwen3.6-plus` |
| GrillMyCode - OpenRouter - Step 3.5 Flash | `stepfun/step-3.5-flash` |
| GrillMyCode - OpenRouter - Tencent Hy3 Preview | `tencent/hy3-preview` |

Each action follows the same core process as Pilot #1: it checks out the repository, diffs your code against the starter commit, strips comments, and sends the diff to the model. Unlike Pilot #1, the questions are **not** posted to the Issues list — instead, each action saves its output as a uniquely named Markdown file in the `_assessment/` folder and commits it back to the repository. The filename includes the model name so outputs from all fourteen actions can sit alongside each other and be compared directly.

---

## How to Run an Action Manually

Because the actions are not triggered automatically, you need to launch each one yourself from the GitHub Actions tab.

1. Go to the repository on GitHub and click the **Actions** tab.
2. In the left sidebar, find the workflow you want to run (e.g., **GrillMyCode - Github Models - GPT 4.1**) and click on it.
3. On the right-hand side of the page, click the **Run workflow** button.
4. A small dropdown will appear. Leave the branch set to **main** and click the green **Run workflow** button to confirm.
5. The workflow will appear in the list with a yellow spinner. Click on it to follow its progress in real time.
6. Once it completes (the spinner turns to a green tick), run `git pull` in your Codespace or local clone to fetch the newly committed file.

```bash
git pull
```

The questions will be saved as a Markdown file in the `_assessment/` folder, named after the model that generated them (e.g. `gpt-4.1.md`, `deepseek-v4-pro.md`). After running all fourteen actions, the folder will contain one file per model for easy side-by-side comparison.

> You are free to run any action more than once — for example, after pushing additional code changes. Just be aware that re-running an action will **overwrite** that model's existing questions file in `_assessment/` with the new output.

---

## ⚠️ Critical: Run Only One Action at a Time

**Never start a second action while another is still running.**

All fourteen workflows write their output to the same `_assessment/` folder and commit it back to the repository. Running two or more actions simultaneously will cause commit conflicts and corrupt the output. Always wait for the running action's spinner to show a green tick (completed) or a red x (completed but with errors) before starting the next one.

If you accidentally trigger two actions at the same time, cancel the second one immediately via **Actions → select the running workflow → Cancel workflow** before it reaches its commit step.

---

## Getting Started

### Step 1 — Open the repository in a Codespace

1. On the repository's main page on GitHub, click the green **Code** button.
2. Select the **Codespaces** tab.
3. Click **Create codespace on main**.

GitHub will build and launch a cloud-based development environment in your browser — no local setup required.

> If you prefer, you can clone to your local machine instead. The Codespace is provided for convenience.

### Step 2 — Add one or more code files

Once the Codespace has loaded, open the integrated terminal (**Terminal → New Terminal**) and create/add one or more source code files. You can add a file in **any language** — Python, JavaScript, Java, C#, Bash, etc. The actions analyse whatever code is present.

> **Tip:** To get the most out of this pilot, use a **meaningful amount of code** rather than a minimal snippet. The more substance there is in the submission, the more varied and revealing the generated questions will be — making it much easier to compare model quality. A good source of test code is a **past student submission** from a previous course or assignment. Real student code tends to have a natural range of quality, patterns, and complexity that produces interesting questions. Even a single reasonably sized file (100+ lines) is enough to see a clear difference between models.

### Step 3 — Commit and push your changes to GitHub

Work directly on the `main` branch — no feature branches are needed. Commit and push your changes as you go.

> **Important:** Each time an action runs, it commits a file back to the repository. Before making any changes — whether to your source code or to any workflow file in `.github/workflows/` — always run `git pull` first to ensure your local workspace is in sync with the repository. Skipping this step risks push conflicts with files written by the actions.
>
> ```bash
> git pull
> ```

### Step 4 — Run the actions one at a time

Follow the steps in [How to Run an Action Manually](#how-to-run-an-action-manually) above. Run each of the fourteen actions in sequence, **waiting for one to finish before starting the next**. After each run, do a `git pull` to fetch the latest file from the `_assessment/` folder. Once all fourteen actions have completed, the folder will contain one Markdown file per model, making it easy to compare outputs side by side.

---

## Feedback & Reporting Issues

All and any feedback is welcomed and encouraged — this is exactly what the pilot is for.

If you encounter any problems, have suggestions for improvements, or want to request a feature, please record them in the **GrillMyCode repository's Issues list**:

**[https://github.com/NSCC-ITC-Assessment/GrillMyCode/issues](https://github.com/NSCC-ITC-Assessment/GrillMyCode/issues)**

This is the central place to log anything worth noting, including:

- Questions that feel generic, irrelevant, or off-target for a given model
- Noticeable quality differences between models
- Workflow errors or unexpected behaviour
- Suggestions for how the output format or question style could be improved
- Feature requests or ideas for future development
- Bugs of any kind or things that just feel a bit off

No observation is too small — if something catches your attention, log it.

Thanking everyone in advance!!

---

## Requirements

| Requirement | Details |
|---|---|
| GitHub Models access | Four workflows use `github_token` with `models: read` permission — no extra setup needed |
| OpenRouter API key | Ten workflows require an `OPENROUTER` secret. This has already been set up and you don't need to do anything for configuration |
