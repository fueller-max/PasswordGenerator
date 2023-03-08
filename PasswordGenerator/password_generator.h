#pragma once

#include <string>
#include <memory>
#include <random>
#include <vector>
#include <array>

class password_generator {
public:
	virtual std::string generate() = 0;
	virtual std::string allowed_chars() const = 0;
	virtual size_t length() const = 0;
	virtual void add(std::unique_ptr<password_generator>) = 0;
	virtual ~password_generator() {}
};

class basic_password_generator : public password_generator {
public:
	explicit basic_password_generator(size_t const len) noexcept : len(len) {
	}
	virtual std::string generate() override {
		throw std::runtime_error("not implemented");
	}
	virtual void add(std::unique_ptr<password_generator>) override {
		throw std::runtime_error("not implemented");
	}
	virtual size_t length() const override;
	
private:
	size_t len;
};


class digit_generator final : public basic_password_generator {
public:
	explicit digit_generator(size_t const length) noexcept : 
		basic_password_generator(length) {}
	virtual std::string allowed_chars() const override;
};

class symbol_generator final : public basic_password_generator {
public:
	explicit symbol_generator(size_t const length) noexcept :
		basic_password_generator(length) {}
	virtual std::string allowed_chars() const override;
};

class upper_letter_generator final : public basic_password_generator {
public:
	explicit upper_letter_generator(size_t const length) noexcept :
		basic_password_generator(length) {}
	virtual std::string allowed_chars() const override;
};

class lower_letter_generator final : public basic_password_generator {
public:
	explicit lower_letter_generator(size_t const length) noexcept :
		basic_password_generator(length) {}
	virtual std::string allowed_chars() const override;
};

class composite_password_generator : public password_generator {
public:
	composite_password_generator();
	virtual void add(std::unique_ptr<password_generator>) override;
	virtual std::string generate() override;
	virtual std::string allowed_chars() const override {
		throw std::runtime_error("not implemented");
	}
	virtual size_t length() const override {
		throw std::runtime_error("not implemented");
	}

private:
	std::random_device rd;
	std::mt19937 eng;
    std::vector<std::unique_ptr<password_generator>> generators;
};