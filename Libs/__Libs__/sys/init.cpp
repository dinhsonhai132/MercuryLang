#include <Mercury.h>
#include "sys.hpp"

START_DLL

DLL_EXPORT table* sys_cmd(table* args[]) {
    if (args[0]->is_str) {
        return MER_VALUE(sys_cmd(__convert_to_string(args[0]->f_str_v)));
    }

    return MER_VALUE(-1);
}

DLL_EXPORT table* __write_file_content(table* args[]) {
    table *path = args[0];
    table *content = args[1];

    if (path->is_str && content->is_str) {
        return MER_VALUE(write_file_content(__convert_to_string(path->f_str_v), __convert_to_string(content->f_str_v)));
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __list_dir(table* args[]) {
    if (args[0]->is_str) {
        vector<string> files = list_dir(__convert_to_string(args[0]->f_str_v));

        table *list = MerCompiler_Table_new();
        list->is_list = true;
        list->list_v = MerCompiler_list_object_new();

        for (auto &file : files) {
            vector<uint8_t> uint8tfile = string_to_uint8_t(file);

            mString_T *str = MerCompiler_string_new();
            str->buff = uint8tfile;
            str->size = file.size();

            table *str_tab = MerCompiler_Table_new();
            str_tab->is_str = true;
            str_tab->f_str_v = str;
            str_tab->cval = __hash(str);
            str_tab->value = str_tab->cval;

            list->list_v->args.push_back(str_tab);
            list->list_v->size++;
        }

        return list;
    }
    else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __read_file_content(table* args[]) {
    if (args[0]->is_str) {
        string content = sys_get_content(__convert_to_string(args[0]->f_str_v));
        mString_T *str = make_str_obj(content);
        table *str_tab = MerCompiler_Table_new();
        str_tab->is_str = true;
        str_tab->f_str_v = str;
        str_tab->cval = __hash(str);
        str_tab->value = str_tab->cval;
        return str_tab;
    } else {
        return MER_VALUE(-1);
    }

    return MER_VALUE(-1);
}

DLL_EXPORT table* __is_file_exists(table* args[]) {
    mBool_T *bool_obj = make_bool(file_exists(__convert_to_string(args[0]->f_str_v)));
    table *bool_tab = MerCompiler_Table_new();
    bool_tab->is_bool = true;
    bool_tab->bool_v = bool_obj;
    bool_tab->cval = bool_obj->value;
    bool_tab->value = bool_tab->cval;
    return bool_tab;
}

DLL_EXPORT table* __is_file(table* args[]) {
    bool is_file_val = is_file(__convert_to_string(args[0]->f_str_v));
    mBool_T *bool_obj = make_bool(is_file_val);
    table *bool_tab = MerCompiler_Table_new();
    bool_tab->is_bool = true;
    bool_tab->bool_v = bool_obj;
    bool_tab->cval = bool_obj->value;
    bool_tab->value = bool_tab->cval;

    return bool_tab;
}

DLL_EXPORT table* __get_file_size(table* args[]) {
    if (args[0]->is_str) {
        size_t size = file_size(__convert_to_string(args[0]->f_str_v));
        return MER_VALUE(size);
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __delete_file(table* args[]) {
    if (args[0]->is_str) {
        mBool_T *bool_obj = make_bool(remove_file(__convert_to_string(args[0]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __create_file(table* args[]) {

    if (args[0]->is_str) {
        mBool_T *bool_obj = make_bool(create_file(__convert_to_string(args[0]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __create_dir(table* args[]) {
    if (args[0]->is_str) {
        mBool_T *bool_obj = make_bool(create_dir(__convert_to_string(args[0]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __delete_dir(table* args[]) {
    if (args[0]->is_str) {
        mBool_T *bool_obj = make_bool(remove_dir(__convert_to_string(args[0]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __is_dir(table* args[]) {
    if (args[0]->is_str) {
        bool is_dir_val = is_dir(__convert_to_string(args[0]->f_str_v));
        mBool_T *bool_obj = make_bool(is_dir_val);
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __rename_file(table* args[]) {
    if (args[0]->is_str && args[1]->is_str) {
        mBool_T *bool_obj = make_bool(rename_file(__convert_to_string(args[0]->f_str_v), __convert_to_string(args[1]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __rename_dir(table* args[]) {
    if (args[0]->is_str && args[1]->is_str) {
        mBool_T *bool_obj = make_bool(rename_dir(__convert_to_string(args[0]->f_str_v), __convert_to_string(args[1]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __copy_file(table* args[]) {
    if (args[0]->is_str && args[1]->is_str) {
        mBool_T *bool_obj = make_bool(copy_file(__convert_to_string(args[0]->f_str_v), __convert_to_string(args[1]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table *__move_file(table *args[]) {
    if (args[0]->is_str && args[1]->is_str) {
        mBool_T *bool_obj = make_bool(move_file(__convert_to_string(args[0]->f_str_v), __convert_to_string(args[1]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __move_dir(table* args[]) {
    if (args[0]->is_str && args[1]->is_str) {
        mBool_T *bool_obj = make_bool(move_dir(__convert_to_string(args[0]->f_str_v), __convert_to_string(args[1]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

DLL_EXPORT table* __copy_dir(table* args[]) {
    if (args[0]->is_str && args[1]->is_str) {
        mBool_T *bool_obj = make_bool(copy_dir(__convert_to_string(args[0]->f_str_v), __convert_to_string(args[1]->f_str_v)));
        table *bool_tab = MerCompiler_Table_new();
        bool_tab->is_bool = true;
        bool_tab->bool_v = bool_obj;
        bool_tab->cval = bool_obj->value;
        bool_tab->value = bool_tab->cval;
        return bool_tab;
    } else {
        return MER_VALUE(-1);
    }
}

END_DLL