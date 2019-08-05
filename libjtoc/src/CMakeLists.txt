cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(jtoc PUBLIC
        jtoc_read_file.c
        jtoc_validate.c
        jtoc_validate_value.c
        jtoc_parse.c
        jtoc_parse_value.c
        jtoc_parse_number.c
        jtoc_utils.c
        jtoc_utils2.c
        jtoc_node.c
        jtoc_read.c
        jtoc_get.c
        jtoc_get_raw_data.c
        jtoc_write.c
        )