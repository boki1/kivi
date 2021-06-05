/**
 * Optional ref implementation
 * Taken from https://github.com/hpesoj/gsl-pointers.
 *
 * All rights reserved to Joseph Thomson
 */

/*
 * Copyright (c) 2016 - 2019 Joseph Thomson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef GSL_OPTIONAL_REF_HPP
#define GSL_OPTIONAL_REF_HPP

#include <cstddef>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

namespace gsl
{
	template<typename T>
	class optional_ref
	{
		template<typename>
		friend
		class optional_ref;

	 public:
		using value_type = T&;

		constexpr optional_ref() noexcept
			: m_ptr()
		{
		}

		constexpr optional_ref(std::nullopt_t) noexcept
			: m_ptr()
		{
		}

		constexpr optional_ref(T& t) noexcept
			: m_ptr(std::addressof(t))
		{
		}

		optional_ref& operator=(optional_ref const&) = delete;

		template<typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*>>>
		optional_ref(optional_ref<U> const& other) noexcept
			: m_ptr(other.m_ptr)
		{
		}

		constexpr bool has_value() const noexcept
		{
			return m_ptr != nullptr;
		}

		constexpr explicit operator bool() const noexcept
		{
			return has_value();
		}

		constexpr T& operator*() const
		{
			return *m_ptr;
		}

		constexpr T* operator->() const
		{
			return m_ptr;
		}

		constexpr T& value() const
		{
			if (!has_value())
			{
				throw std::bad_optional_access();
			}

			return *m_ptr;
		}

		template<
			typename U,
			typename T_ = T,
			typename = std::enable_if_t<std::is_copy_constructible_v<T_>>>
		constexpr T_ value_or(U&& default_value) const
		{
			return has_value() ? **this : static_cast<T>(std::forward<U>(default_value));
		}

	 private:
		T* m_ptr;
	};

	template<typename T>
	constexpr optional_ref<T> make_optional_ref(T& t) noexcept
	{
		return t;
	}

	template<typename T>
	constexpr bool operator==(optional_ref<T> const& lhs, optional_ref<T> const& rhs)
	{
		return (bool(lhs) != bool(rhs)) ? false : (bool(lhs) == false) ? true : *lhs == *rhs;
	}

	template<typename T>
	constexpr bool operator!=(optional_ref<T> const& lhs, optional_ref<T> const& rhs)
	{
		return (bool(lhs) != bool(rhs)) ? true : (bool(lhs) == false) ? false : *lhs != *rhs;
	}

	template<typename T>
	constexpr bool operator<(optional_ref<T> const& lhs, optional_ref<T> const& rhs)
	{
		return (bool(rhs) == false) ? false : (bool(lhs) == false) ? true : *lhs < *rhs;
	}

	template<typename T>
	constexpr bool operator<=(optional_ref<T> const& lhs, optional_ref<T> const& rhs)
	{
		return (bool(lhs) == false) ? true : (bool(rhs) == false) ? false : *lhs <= *rhs;
	}

	template<typename T>
	constexpr bool operator>(optional_ref<T> const& lhs, optional_ref<T> const& rhs)
	{
		return (bool(lhs) == false) ? false : (bool(rhs) == false) ? true : *lhs > *rhs;
	}

	template<typename T>
	constexpr bool operator>=(optional_ref<T> const& lhs, optional_ref<T> const& rhs)
	{
		return (bool(rhs) == false) ? true : (bool(lhs) == false) ? false : *lhs >= *rhs;
	}

	template<typename T>
	constexpr bool operator==(optional_ref<T> const& opt, std::nullopt_t) noexcept
	{
		return !opt;
	}

	template<typename T>
	constexpr bool operator==(std::nullopt_t, optional_ref<T> const& opt) noexcept
	{
		return !opt;
	}

	template<typename T>
	constexpr bool operator!=(optional_ref<T> const& opt, std::nullopt_t) noexcept
	{
		return bool(opt);
	}

	template<typename T>
	constexpr bool operator!=(std::nullopt_t, optional_ref<T> const& opt) noexcept
	{
		return bool(opt);
	}

	template<typename T>
	constexpr bool operator<(optional_ref<T> const& opt, std::nullopt_t) noexcept
	{
		return false;
	}

	template<typename T>
	constexpr bool operator<(std::nullopt_t, optional_ref<T> const& opt) noexcept
	{
		return bool(opt);
	}

	template<typename T>
	constexpr bool operator<=(optional_ref<T> const& opt, std::nullopt_t) noexcept
	{
		return !opt;
	}

	template<typename T>
	constexpr bool operator<=(std::nullopt_t, optional_ref<T> const& opt) noexcept
	{
		return true;
	}

	template<typename T>
	constexpr bool operator>(optional_ref<T> const& opt, std::nullopt_t) noexcept
	{
		return bool(opt);
	}

	template<typename T>
	constexpr bool operator>(std::nullopt_t, optional_ref<T> const& opt) noexcept
	{
		return false;
	}

	template<typename T>
	constexpr bool operator>=(optional_ref<T> const& opt, std::nullopt_t) noexcept
	{
		return true;
	}

	template<typename T>
	constexpr bool operator>=(std::nullopt_t, optional_ref<T> const& opt) noexcept
	{
		return !opt;
	}

	template<typename T>
	constexpr bool operator==(optional_ref<T> const& opt, T const& value)
	{
		return bool(opt) ? *opt == value : false;
	}

	template<typename T>
	constexpr bool operator==(T const& value, optional_ref<T> const& opt)
	{
		return bool(opt) ? value == *opt : false;
	}

	template<typename T>
	constexpr bool operator!=(optional_ref<T> const& opt, T const& value)
	{
		return bool(opt) ? *opt != value : true;
	}

	template<typename T>
	constexpr bool operator!=(T const& value, optional_ref<T> const& opt)
	{
		return bool(opt) ? value != *opt : true;
	}

	template<typename T>
	constexpr bool operator<(optional_ref<T> const& opt, T const& value)
	{
		return bool(opt) ? *opt < value : true;
	}

	template<typename T>
	constexpr bool operator<(T const& value, optional_ref<T> const& opt)
	{
		return bool(opt) ? value < *opt : false;
	}

	template<typename T>
	constexpr bool operator<=(optional_ref<T> const& opt, T const& value)
	{
		return bool(opt) ? *opt <= value : true;
	}

	template<typename T>
	constexpr bool operator<=(T const& value, optional_ref<T> const& opt)
	{
		return bool(opt) ? value <= *opt : false;
	}

	template<typename T>
	constexpr bool operator>(optional_ref<T> const& opt, T const& value)
	{
		return bool(opt) ? *opt > value : false;
	}

	template<typename T>
	constexpr bool operator>(T const& value, optional_ref<T> const& opt)
	{
		return bool(opt) ? value > *opt : true;
	}

	template<typename T>
	constexpr bool operator>=(optional_ref<T> const& opt, T const& value)
	{
		return bool(opt) ? *opt >= value : false;
	}

	template<typename T>
	constexpr bool operator>=(T const& value, optional_ref<T> const& opt)
	{
		return bool(opt) ? value >= *opt : true;
	}

} // namespace gsl

namespace std
{
	template<typename T>
	struct hash<gsl::optional_ref<T>>
	{
		constexpr std::size_t operator()(gsl::optional_ref<T> const& opt) const noexcept
		{
			return bool(opt) ? hash<T>()(*opt) : hash<void*>()(nullptr);
		}
	};

} // namespace std

#endif // GSL_OPTIONAL_REF_HPP
