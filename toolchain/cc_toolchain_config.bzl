load("@rules_cc//cc:action_names.bzl", "ACTION_NAMES")
load("@rules_cc//cc/common:cc_common.bzl", "cc_common")
load("@rules_cc//cc:cc_toolchain_config_lib.bzl",  "feature", "flag_set", "flag_group")

def _impl(ctx):
    # Define the base path for compiler utilities
    compiler_bin_path = "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-"
    # Define the path to the include directory
    compiler_include_path = "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/arm-none-eabi/include"
    
    # Specify the exact path to your local toolchain binaries
    tool_paths = [
        struct(name = "gcc", path = compiler_bin_path + "gcc"),
        struct(name = "cpp", path = compiler_bin_path + "g++"),
        struct(name = "ld", path = compiler_bin_path + "ld"),
        struct(name = "nm", path = compiler_bin_path + "nm"),
        struct(name = "ar", path = compiler_bin_path + "ar"),
        struct(name = "strip", path = compiler_bin_path + "strip"),
        struct(name = "objcopy", path = compiler_bin_path + "objcopy"),
        struct(name = "objdump", path = compiler_bin_path + "objdump"),
    ]

    # Combine all actions for compilation and linking
    all_compile_actions = [
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.assemble,
        ACTION_NAMES.preprocess_assemble,
    ]
    all_link_actions = [
        ACTION_NAMES.cpp_link_executable,
    ]

    # 2. Package global hardware specs as a Bazel Feature
    hardware_flags_feature = feature(
        name = "hardware_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = all_compile_actions + all_link_actions,
                flag_groups = [
                    flag_group(
                        flags = [
                            "-mcpu=cortex-m4",
                            "-mfpu=fpv4-sp-d16",
                            "-mfloat-abi=soft",  # Using the soft ABI flag from your IDE specs
                            "-mthumb",
                            "--specs=nano.specs",
                        ],
                    ),
                ],
            ),
        ],
    )

    features = [hardware_flags_feature]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        action_configs = [],
        artifact_name_patterns = [],
        cxx_builtin_include_directories = [
            # Tells Bazel where it's safe to look for compiler-provided headers.
            # If your toolchain throws missing standard header errors later,
            # we will explicitly add your system toolchain include paths here.
            compiler_include_path,
        ],
        toolchain_identifier = "local_arm_none_eabi",
        host_system_name = "local",
        target_system_name = "arm-none-eabi",
        target_cpu = "cortex-m4",
        target_libc = "unknown",
        compiler = "arm-none-eabi-gcc",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
)