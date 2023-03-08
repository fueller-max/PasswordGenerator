#include<stdexcept>
#include "password_generator.h"


  size_t basic_password_generator :: length() const {
	  return len;
  }


  std::string digit_generator::allowed_chars() const {
	  return "0123456789";
  }

  std::string symbol_generator::allowed_chars() const {
	  return "!@#$%^&*{}<>";
  }

  std::string upper_letter_generator::allowed_chars() const {
	  return "ABCDEFGHIJKLMNOPQRSTUVXVYWZ";
  }

  std::string lower_letter_generator::allowed_chars() const {
	  return "abcdefghjklmnopqrstuvxvywz";
  }



  composite_password_generator::composite_password_generator() {
	  auto seed_data = std::array<int, std::mt19937::state_size>{};
	  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
	  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
	  eng.seed(seq);
  }
   
  void composite_password_generator::add(std::unique_ptr<password_generator> generator) {
	  generators.push_back(std::move(generator));
  }

  std::string composite_password_generator::generate() {
	  std::string password;
	  for (auto& generator : generators) {
		  std::string chars = generator->allowed_chars();
		  std::uniform_int_distribution<> ud(
			  0, static_cast<int>(chars.length() - 1));

		  for (size_t idx = 0; idx < generator->length(); ++idx) {
			  password += chars[ud(eng)];
		  }
	  }

	  std::shuffle(std::begin(password), std::end(password), eng);

	  return password;
  }

