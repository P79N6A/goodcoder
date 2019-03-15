BEGIN {
    query_num = 0
    succ_num = 0
    total_value = 0
    name_num = 0
    name_array[1] = 0
}
{
    #if (NF == 10) {
        query_num = query_num + 1
        split($7, succ_cell, "=")
        if (succ_cell[2] == "1") {
            # 成功返回数据，则成功次数加1 
            succ_num = succ_num + 1; 
            # 累加 value
            split($11, value_cell, "=")
            total_value = total_value + value_cell[2]
            # 统计 name 次数，并避免重复
            duplicate_flag = 0
            split($9, name_cell, "=")
            for (name in name_array) {
                if (name == name_cell[2]) {
                    duplicate_flag = 1
                }
            }
            if (duplicate_flag == 0) {
                name_num = name_num + 1
                name_array[name_num] = name_cell[2]
            }
        }
    #}
}
END {
    printf "value_avg=%f\n", total_value / succ_num
    printf "succ_rate=%f\n", succ_num / query_num
    printf "name_num=%d\n", name_num
}
