# 学习进度与交接

这份文件记录换机器时需要知道的状态。每次完成一个学习步骤后，更新“最近进度”“验证情况”和“下一步”，再与代码一起提交、推送。

## 当前状态（2026-10-20，Windows）

- 阶段：PA2-1 的代码、课程测试与实验报告整理已完成。
- 最近进度：完成算术、逻辑和比较指令的宏实现，补齐栈操作、调用、返回及条件判断，并接入主操作码表、双字节表和 group 表。
- 最后停点：`hello-str` 使用 `FF /4` 间接跳转；已在 `jmp.c` 增加 `jmp_near_indirect`，读取寄存器或内存中的绝对目标地址，并补偿执行循环随后增加的指令长度及前缀长度。
- 本次用户授权：用户明确要求助手补齐剩余条件宏与最后的指令实现。今后的教学仍按 `AGENTS.md` 的默认分工进行。
- 最终验证：完整重新编译成功；按 `Makefile` 的 `test_pa-2-1` 列表逐一执行全部 31 个用例，结果为 **30 个 HIT GOOD TRAP、`test-float` 按课程要求 HIT BAD TRAP、0 个失败**。`hello-str` 的 Good Trap 地址为 `0x000300d8`。
- 先前同步点：`405148a`（`WIP: sync PA2-1 instruction progress`）是旧的进度快照；本文件的最新结果以此次实际编译、测试为准。
- 实验报告：`reports/PA2-1实验报告.md` 保存可版本管理的正文；Windows 上另生成三页 Word 文件 `D:\NEMUcodes\output\doc\PA2-1实验报告_251220035.docx`。署名沿用已有 PA1 报告的胡展赫、251220035，包含实现过程、三道思考题和实际测试结论。Word 文件通过本机 Microsoft Word 导出预览并逐页检查；该附件位于仓库外，换机器时需单独复制。

### 验证命令与环境

在仓库根目录使用 WSL。旧工程在当前 GCC 下需要明确指定 GNU C11 和 32 位编译、链接参数：

```powershell
wsl make -B -C nemu -j4 'CFLAGS=-ggdb3 -MMD -MP -Wall -Werror -O2 -std=gnu11 -m32 -I./include -I../include -I../libs -I../libs/nemu-ref/include' 'LDFLAGS=-m32 -lreadline -lSDL'
wsl ./nemu/nemu --autorun --testcase hello-str
```

完整回归对 `Makefile` 中 `test_pa-2-1` 列出的每个用例分别执行上述 `--testcase` 命令。`test-float` 的验收结果是 Bad Trap，其他 30 项应为 Good Trap。配置中的 `NEMU_REF_INSTR` 保持关闭。根目录的 `make test_pa-2-1` 会执行自动 Git 提交，本次通过逐项运行测试完成验证。

### 下一步

- 提交前核对课程要求的报告格式及署名。三道思考题已整理，代码验证日期为2026-10-19，报告整理日期为2026-10-20。
- 2026-10-20：已同步到 NEMU 平台 `/home/pa251220035/pa_nju`，保留平台原有历史与 PA1 成绩记录。平台默认环境重新编译并运行全部31项测试：30项 GOOD、test-float 预期 BAD、0项失败。日志位于平台 `~/temp/pa2-1-*.log`。
- 平台版本来自本地成果提交 `378b3dc`。Word报告副本放在平台 `~/temp/PA2-1_report_251220035.docx`。
- 2026-10-20：用户确认声明后，已在平台运行 `make submit_pa-2-1`。平台返回 `Submission sequence completed`，完整性检查、重编译与打包通过。提交测试：30项GOOD，test-float预期BAD。
- 压缩包：`~/submit/251220035_pa-2-1_1792481841.tar.bz2`。本地副本：`D:/NEMUcodes/submit/251220035_pa-2-1_1792481841.tar.bz2`。
- 下一步：上传压缩包至cslab备用窗口，并上传报告；网页上传尚未完成。

## 换机器时

1. 在开始学习的机器上进入本仓库，运行 `git pull --ff-only` 和 `git status`；如果有未提交改动或拉取失败，先检查差异。
2. 阅读本文件和 `AGENTS.md`，确认当前任务及课件位置。
3. 结束时更新本文件，检查改动，提交并运行 `git push`。

## 后续更新模板

- 日期与机器：
- 本次完成：
- 编译和测试（命令、结果）：
- 尚未解决的问题：
- 下一步小练习：
