#include <iostream>
#include <map>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::map;
using std::int32_t;
using std::string;
using std::array;

struct context {
    map<string, int32_t> vars;
    map<string, int32_t> cached_vars;
    struct context* parent;
};

struct context* create_context(struct context* parent) {
    map<string, int32_t> vars;
    map<string, int32_t> cached_vars;
    auto ctx = new context;
    *ctx = { .vars = vars, .cached_vars = cached_vars, .parent = parent };
    return ctx;
}


array<string, 2> split_equality(const string eq) {
    size_t delimiter_index = eq.find('=');
    string first = eq.substr(0, delimiter_index);
    string second = eq.substr(delimiter_index + 1);
    return { first, second };
}

bool get_int32(string s, int32_t &value) {
    std::stringstream stream(s);
    stream >> value;
    return !stream.fail();
}

int32_t get_context_value(map<string, int32_t> &ctx, const string &var) {
    if (ctx.find(var) == ctx.end()) {
        return 0;
    }
    return ctx[var];
}

void restore_context(map<string, int32_t> &global_ctx, context* ctx) {
    for (auto const& pair : ctx->cached_vars) {
        global_ctx[pair.first] = pair.second;
    }
}

void cache_var(map<string, int32_t> &global_ctx, context* ctx, const string &var) {
    if (ctx->cached_vars.find(var) == ctx->cached_vars.end()) {
        if (global_ctx.find(var) != global_ctx.end()) {
            ctx->cached_vars[var] = global_ctx[var];
        } else {
            ctx->cached_vars[var] = 0;
        }
    }
}

int main() {
    context *current_ctx = create_context(nullptr);
    map<string, int32_t> config_context;
    string line;
    while (getline(cin, line)) {
        if (line == "{") {
            context *temp = current_ctx;
            current_ctx = create_context(temp);
        } else if (line == "}") {
            context *temp = current_ctx;
            current_ctx = current_ctx->parent;
            restore_context(config_context, temp);
            delete temp;
        } else {
            array<string, 2> pair = split_equality(line);
            int32_t value;
            if (get_int32(pair[1], value)) {
                cache_var(config_context, current_ctx, pair[0]);
                current_ctx->vars[pair[0]] = value;
                config_context[pair[0]] = value;
            } else {
                cache_var(config_context, current_ctx, pair[0]);
                value = get_context_value(config_context, pair[1]);
                current_ctx->vars[pair[0]] = value;
                config_context[pair[0]] = value;
                cout << value << "\n";
            }
        }
    }
    return 0;
}
