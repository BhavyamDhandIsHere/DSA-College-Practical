
void write_text_to_log_file( const std::string &text )
{
    std::ofstream log_file(
        "log_file.txt", ios_base::out | ios_base::app );
    log_file << text<<endl;
}
