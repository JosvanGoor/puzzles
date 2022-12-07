#include <charconv>
#include <fmt/format.h>
#include <iostream>
#include <map>

struct Entry
{
    int size{}; // -1 = dir
    std::map<std::string, std::shared_ptr<Entry>> entries;
};
using EntryPtr = std::shared_ptr<Entry>;

std::uint64_t calculate(std::uint64_t& score, const EntryPtr& entry)
{
    if (entry->size != -1)
        return entry->size;
    
    std::uint64_t size{};
    for (const auto& [name, ptr] : entry->entries)
    {
        if (name == "..")
            continue;
        size += calculate(score, ptr);
    }

    if (size <= 100'000)
        score += size;
    return size;
}

std::uint64_t find(std::uint64_t& score, const EntryPtr& entry, std::uint64_t free_required)
{
    if (entry->size != -1)
        return entry->size;

    std::uint64_t size{};
    for (const auto& [name, ptr] : entry->entries)
    {
        if (name == "..")
            continue;
        size += find(score, ptr, free_required);
    }

    if (size >= free_required)
        score = std::min(score, size);

    return size;
}

void print_folder(const std::string& name, const EntryPtr& folder, int level = 0)
{
    if (name == "..")
        return;
    fmt::print("{:{}}-", ' ', level);
    if (folder->size == -1)
    {
        fmt::print("{}\n", name);
        for (const auto& [folder_name, entry] : folder->entries)
            print_folder(folder_name, entry, level + 4);
    }
    else
        fmt::print("{} (size: {})\n", name, folder->size);
}

int main()
{
    std::string buffer;
    EntryPtr root = std::make_shared<Entry>();
    root->size = -1;
    EntryPtr current;

    while (true)
    {
        std::getline(std::cin, buffer);
        if (buffer.find("$ c") == 0)
        {
            auto folder = buffer.substr(5);
            
            if (folder == "/")
                current = root;
            else
                current = current->entries[folder];
        }
        else if (buffer.find("$ l") == 0)
        { } // nothing?
        else if (buffer[0] == 'd') // dir
        {
            auto name = buffer.substr(4);
            auto entry = std::make_shared<Entry>();
            entry->size = -1;
            entry->entries[".."] = current;
            current->entries[name] = entry;
        }
        else
        {
            auto entry = std::make_shared<Entry>();
            std::from_chars(buffer.data(), buffer.data() + buffer.size(), entry->size);
            current->entries[buffer.substr(buffer.find(' ') + 1)] = entry;
        }

        if (std::cin.eof())
            break;
    }

    // print_folder("/", root);

    std::uint64_t score{};
    std::uint64_t to_free = 70'000'000;

    std::uint64_t total_size = calculate(score, root);
    find(to_free, root, 30'000'000 - (70'000'000 - total_size));

    fmt::print("Result part 1: {}\n", score);
    fmt::print("Result part 2: {}\n", to_free);
}